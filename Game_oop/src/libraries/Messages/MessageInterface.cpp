#include "MessageInterface.h"

std::ostream& operator<<(std::ostream& out, MessageInterface& msg_interface) {
    out << msg_interface.to_string();
    return out;
}