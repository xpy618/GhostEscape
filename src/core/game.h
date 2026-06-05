#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp>
#include <string>
#include <random>
#include "asset_store.h"

struct Texture;
class Scene;
class Game
{
    AssetStore* asset_store_ = nullptr; //资源管理器
    glm::vec2 screen_size_ = glm::vec2(0);
    glm::vec2 mouse_pos_ = glm::vec2(0);
    SDL_MouseButtonFlags mouse_button_ = 0;
    
    bool is_running_ = true;
    Scene* current_scene_ = nullptr; //当前场景
    Scene* next_scene_ = nullptr; //下一个场景

    Uint64 FPS_ = 60;
    Uint64 frame_delay_ = 0; //帧延迟
    float dt_ = 0.0f; //帧间隔

    int score_ = 0;
    int high_score_ = 0;

    SDL_Window* window_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;
    TTF_TextEngine* ttf_engine_ = nullptr;

    std::mt19937 gen_ = std::mt19937(std::random_device{}());

    Game(){}
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

public:
    static Game& getInstance()  //提供全局调用入口
    {
        static Game instance;  //保证实例唯一，懒加载，常驻内存
        return instance;
    }

    void run();
    void init(std::string title, int width, int height);
    void handleEvent();
    void update(float dt);
    void render();
    void clean();

    //getters and setters
    glm::vec2 getScreenSize() const { return screen_size_;}
    Scene* getCurrentScene() const { return current_scene_;}
    AssetStore* getAssetStore() const { return asset_store_;}
    glm::vec2 getMousePosition() const { return mouse_pos_;}
    SDL_MouseButtonFlags getMouseButtons() const { return mouse_button_;}
    int getScore() const { return score_;}
    int getHighScore() const { return high_score_;}
    void setScore(int score);
    void setHighScore(int high_score) { high_score_ = high_score;}

    void addScore(int score);
    void quit() { is_running_ = false; }
    void changeScene(Scene* scene);
    void safeChangeScene(Scene* scene){ next_scene_ = scene; }

    //音频函数
    void playMusic(const std::string& music_path, bool loop = true) { Mix_PlayMusic(asset_store_->getMusic(music_path), loop ? -1 : 0); }
    void playSound(const std::string& sound_path) { Mix_PlayChannel(-1, asset_store_->getSound(sound_path), 0); }
    void stopMusic() { Mix_HaltMusic(); }
    void stopSound() { Mix_HaltChannel(-1); }
    void pauseMusic() { Mix_PauseMusic(); }
    void pauseSound() { Mix_Pause(-1); }
    void resumeMusic() { Mix_ResumeMusic(); }
    void resumeSound() { Mix_Resume(-1); }

    //随机数
    float randomFloat(float min, float max) { return std::uniform_real_distribution<float>(min, max)(gen_); }
    int randomInt(int min, int max) { return std::uniform_int_distribution<int>(min, max)(gen_); }
    glm::vec2 randomVec2(const glm::vec2& min, const glm::vec2& max) { return glm::vec2(randomFloat(min.x, max.x), randomFloat(min.y, max.y)); }
    glm::vec2 randomIvec2(const glm::ivec2& min, const glm::ivec2& max) { return glm::vec2(randomInt(min.x, max.x), randomInt(min.y, max.y)); }

    //渲染函数
    void renderTexture(const Texture& texture, const glm::vec2& position, const glm::vec2& size, const glm::vec2 &mask = glm::vec2(1.0f));
    void renderFillCircle(const glm::vec2& position, const glm::vec2& size, float alpha);
    void renderHBar(const glm::vec2& position, const glm::vec2& size, float percent, SDL_FColor color);
    void drawGrid(const glm::vec2& top_left, const glm::vec2 bottom_right, float grid_size, SDL_FColor fcolor);
    void drawBoundary(const glm::vec2& top_left, const glm::vec2 bottom_right, float boundary_size, SDL_FColor fcolor);
    void drawPoints(const std::vector<glm::vec2>& points, glm::vec2 render_pos, SDL_FColor fcolor);

    //文字函数
    TTF_Text* createTTF_Text(const std::string& text, const std::string& font_path, int font_size = 16);

    //工具函数
    bool isMouseInRect(const glm::vec2& top_left, const glm::vec2& bottom_right);
    std::string loadTextFile(const std::string& file_path);
    bool isRectCollideRect(const glm::vec2& rect1_top_left, const glm::vec2& rect1_bottom_right, const glm::vec2& rect2_top_left, const glm::vec2& rect2_bottom_right);
    bool isRectInRect(const glm::vec2& rect1_top_left, const glm::vec2& rect1_bottom_right, const glm::vec2& rect2_top_left, const glm::vec2& rect2_bottom_right);
    void updateMouse();

};

#endif // GAME_H