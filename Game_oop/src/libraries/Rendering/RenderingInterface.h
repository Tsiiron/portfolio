#ifndef rendering_interface_h
#define rendering_interface_h

class PlayerHandler;
enum class Messages;

class RenderingInterface {
public:
    virtual ~RenderingInterface() = default;
    virtual void print_game(PlayerHandler* handler) = 0;
    virtual void print_message(Messages message) = 0;
};  

#endif