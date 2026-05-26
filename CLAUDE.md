# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## 基本规则

- 操作系统是 Windows 11。路径和命令优先使用 Windows 风格，例如 `D:\GameDev\GhostEscape`、`taskkill //F //IM xxx.exe`。
- 与用户交流始终使用中文。
- 除非用户明确说"修改代码""帮我改""实现"等等，否则默认只读代码、分析原因、给出建议，不修改项目源码、配置或资源文件。
- 改动必须小而直接。不要做无关重构，不整理附近代码，不删除无关死代码。

## 技术栈与构建

- **语言**：C++17
- **构建系统**：CMake 3.10+
- **编译器**：MSVC（Windows）
- **依赖库**：SDL3、SDL3_image、SDL3_mixer、SDL3_ttf、glm

```bash
# 配置（从项目根目录）
cmake -B build -S .

# 编译
cmake --build build
```

构建产物（`GhostEscape-Windows.exe` 和 `.pdb`）直接输出到项目根目录。项目没有测试套件。

## 核心架构

### 对象层级

```
Object (core/object.h)
├── ObjectScreen (core/object_screen.h)    — 屏幕坐标，render_position_ 直接对应窗口像素
│   ├── HUDStats、UIMouse 等 UI 元素
│   └── 作为 ObjectAffiliate 的 parent_
└── ObjectWorld (core/object_world.h)      — 世界坐标，update() 时自动 worldToScreen
    └── Actor (core/actor.h)               — 有 Stats、Collider、velocity_ 的可移动对象
        ├── Player (player.h)
        └── Enemy  (enemy.h)

ObjectAffiliate (core/object_affiliate.h)   — 独立层级，继承 Object，挂载到 ObjectScreen
├── Sprite / SpriteAnim                     — 渲染用精灵，通过 parent_->getRenderPosition() 定位
├── Collider                                — 碰撞检测，通过 parent_ 获取世界坐标
└── AffiliateBar                            — 敌人头顶血条（纯色填充，非纹理）
```

**关键点**：
- `Object` 持有 `Game& game = Game::GetInstance()`，所有子类可直接使用 `game`。
- `ObjectAffiliate` 不继承 `ObjectScreen`/`ObjectWorld`，它通过 `parent_` 指针访问父对象的位置。其 `offset_` 和 `size_` 通过 `Anchor` 枚举自动计算（见 `setOffsetByAnchor()`）。
- `Actor` 的 `stats_` 是独立 `Object` 子节点，HP/Mana 变更发生在 Stats 对象上，外部通过 `getStats()->getHp()` 等访问。

### 静态工厂方法（addChild 模式）

几乎所有类都使用 `static X* addXChild(parent, ...)` 静态方法构造对象。该方法内部完成：创建对象 → 设置 parent → 设置参数 → `parent->safeAddChild(this)`。例如：

```cpp
// 创建一个 Sprite 挂载到 Player 上
Sprite::addSpriteChild(player, "assets/sprite/ghost-idle.png", 1.0f, Anchor::CENTER);
// 内部自动调用了 player->safeAddChild(sprite)
```

新功能开发应遵循此模式，不要在外部手动 new + addChild。

### 场景三容器系统

`Scene` (core/scene.h) 覆写了 `addChild()`，根据 `ObjectType` 将对象分入三个独立容器：

| ObjectType | 容器 | 用途 |
|---|---|---|
| `OBJECT_SCREEN` | `children_screen_` | UI 元素，渲染时无视相机 |
| `OBJECT_WORLD` / `ENEMY` | `children_world_` | 游戏实体，渲染时减去相机偏移 |
| `NONE` | `children_`（基类） | 附属组件等 |

`Scene::update()` 和 `Scene::render()` 按先 world 后 screen 的顺序遍历这些容器。`Scene::addChild()` 依赖正确的 `ObjectType` 设置，必须通过 `ObjectScreen::init()` 或 `ObjectWorld::init()` 设置 type，否则对象会进入错误的容器。

### 坐标系统

- **世界坐标**：`ObjectWorld::position_`，游戏逻辑使用的坐标，在 `world_size_` 范围内
- **屏幕坐标**：`ObjectWorld::render_position_` / `ObjectScreen::render_position_`，对应窗口像素
- **相机**：`Scene::camera_position_` 表示相机在世界中的左上角位置
- 转换：`worldToScreen(pos) = pos - camera_position_`，在 `ObjectWorld::update()` 中每帧自动执行
- 鼠标位置来自 SDL（屏幕坐标），生成世界对象需要 `mouse_position + camera_position`

### 输入流

```
Game::handleEvent()           — SDL_PollEvent 循环，SDL_EVENT_QUIT 在这里处理
  └→ Scene::handleEvents()    — 转发给 children_screen_ 和 children_world_
       └→ Object::handleEvents() — 各对象自行处理
```

鼠标状态不在 event 中获取：`Game::update()` 每帧通过 `SDL_GetMouseState()` 获取鼠标位置和按键，存入 `mouse_pos_` / `mouse_button_`，各对象在 `update()` 中通过 `game.getMousePosition()` 读取。

### 主循环

`Game::run()` (game.cpp) — 固定时间步长（60 FPS）的主循环：`handleEvent()` → `update(dt)` → `render()`。`dt` 为帧间隔（秒）。窗口使用 `SDL_LOGICAL_PRESENTATION_LETTERBOX` 模式保持逻辑分辨率。

### 延迟添加机制

`Object::safeAddChild()` 将新对象放入 `object_to_add_` 队列。在 `Object::update()` 中（每帧开始时），队列中的对象被移入 `children_`。这意味着在构造期间添加的子对象要到下一帧才会生效。

## 战斗系统

### Weapon → Spell → Collider 链

```
Weapon (raw/weapon.h)                 — 管理冷却计时器和蓝耗
  ├── WeaponThunder (weapon_thunder.h) — 具体武器，响应键盘事件
  └→ attack() 创建 Spell

Spell (world/spell.h)                 — ObjectWorld，带 SpriteAnim
  └→ update() 中遍历 children_world_，用 Collider 检测碰撞 → takeDamage()

Effect (world/effect.h)               — 一次性动画，播完后自动删除
  └→ next_object_ 非空时，动画结束后自动添加到场景
```

- `Weapon::attack()` 先调用 `canAttack()` 检查冷却和蓝量，通过后调用 `Stats::useMana()` 并重置冷却计时器，然后在目标位置创建一个 Spell。
- `Spell::update()` 每帧遍历 `scene->getChildrenWorld()`，用自身的 `collider_` 与每个对象的 collider 做碰撞检测。检测到碰撞后调用 `takeDamage()` 然后标记自身移除。
- 碰撞检测本身在 `Collider::isColliding()` 中（支持 RECTANGLE 和 CIRCLE 两种类型）。`Collider` 是 `Spell` 的友元类。

### Stats 系统（raw/stats.h）

- **HP/MP**：`hp_`、`max_hp_`、`mana_`、`max_mana_`、`damage_`
- **无敌帧**：受伤后 `invincible_time_` 秒内 `is_invincible_` 为 true，不可再次受伤
- **蓝量回复**：每帧 `regenMana(dt)` 自动回复 `mana_regen_` 点
- **伤害流程**：`takeDamage(damage)` → 检查 `!is_invincible_` → 扣血 → 如果 HP ≤ 0 则 `is_alive_ = false`
- Stats 作为 Actor 的子节点（通过 `Stats::addStatsChild(actor, ...)`），挂在 `children_` 中

### Enemy 状态机（enemy.h）

```
NORMAL → HURT → DIE
```

- NORMAL：播放 `anim_normal_`，追踪 Player 位置 (`aimTarget()`)
- HURT：受伤后短暂切换，播放 `anim_hurt_`，然后回到 NORMAL
- DIE：HP ≤ 0 时进入，播放 `anim_die_`，动画结束后调用 `remove()` 创建死亡特效
- Enemy 创建使用 `Enemy::addEnemyChild(parent, pos, target)` 静态方法

## 资源管理

### AssetStore（core/asset_store.h）

- 四种资源类型：Image（`SDL_Texture*`）、Sound（`Mix_Chunk*`）、Music（`Mix_Music*`）、Font（`TTF_Font*`）
- 所有 `get*()` 方法采用懒加载：先查 `unordered_map` 缓存，没有则先 `load*()` 再返回
- 文件路径作为缓存 key
- Game 初始化时创建 AssetStore，传入 `SDL_Renderer*`（纹理加载需要渲染器）

### Texture 结构体（affiliate/sprite.h）

```cpp
struct Texture {
    SDL_Texture* texture;
    SDL_FRect src_rect;   // 源矩形，决定绘制纹理的哪一部分
    float angle;          // 旋转角度
    bool is_flip;         // 是否水平翻转
};
```

Texture 可以从文件路径构造（构造函数内调 `AssetStore::getImage()`），也可以在 Sprite 上动态设置 `angle` 和 `is_flip`。

## 已知问题

- `Game::renderTexture()` (game.cpp:137) 传入了 `&texture.src_rect` 而非 `&src_rect`，导致纹理 mask/percentage 在源矩形上不生效。生命条/法力条通过 `Sprite::percentage_` 控制显示比例时，纹理会被压缩而非裁切。

## 排查优先级

- **坐标/相机问题**：先看 `object_world.cpp`、`scene.h`、具体对象的 `update()` 和 `render()`
- **对象添加/删除问题**：先看 `Object::update()`（延迟添加机制）、`Scene::addChild()`（ObjectType 路由）
- **渲染位置问题**：先确认对象是 `ObjectWorld` 还是 `ObjectScreen`，再看 `ObjectAffiliate` 是否通过 `parent_->getRenderPosition()` 定位
- **碰撞问题**：先看 `ObjectType`（ENEMY 类型会被加入 `children_world_`）、`Collider` 父对象位置同步
- **战斗逻辑问题**：先看 Weapon 的冷却/蓝耗检查（`canAttack()`），再看 Spell 的碰撞检测循环，最后看 Stats 的无敌帧状态
