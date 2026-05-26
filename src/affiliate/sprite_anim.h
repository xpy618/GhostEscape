#ifndef SPRITE_ANIM_H
#define SPRITE_ANIM_H
#include "sprite.h"

class SpriteAnim : public Sprite
{
    int current_frame_ = 0;  //当前帧
    int total_frames_ = 0;  //总帧数
    int fps_ = 10;
    float frame_time_ = 0.0f;  //每帧的时间
    bool is_loop_ = true;
    

public:
    static SpriteAnim* addSpriteAnimChild(ObjectScreen* parent, const std::string& file_path, float scale = 1.0f, Anchor anchor = Anchor::CENTER);
    //静态函数，只要引用头文件就可以全局调用，不需要创建对象
    virtual void update(float dt) override;
    //getters and setters
    virtual void setTexture(const Texture& texture) override ;

    int getCurrentFrame() { return current_frame_; }
    void setCurrentFrame(int current_frame) { current_frame_ = current_frame; }
    int getTotalFrames() { return total_frames_; }
    void setTotalFrames(int total_frames) { total_frames_ = total_frames; }
    int getFps() { return fps_; }
    void setFps(int fps) { fps_ = fps; }
    float getFrameTime() { return frame_time_; }
    void setFrameTime(float frame_time) { frame_time_ = frame_time; }
    bool getLoop() { return is_loop_; }
    void setLoop(bool is_loop) { is_loop_ = is_loop; }
};


#endif // SPRITE_ANIM_H