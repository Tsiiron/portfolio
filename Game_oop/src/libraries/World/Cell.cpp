#include "Cell.h"
#include "algorithm"
#include "Event/MovementEvents/Teleport.h"
#include "Event/NegativeEvents/Trap.h"
#include "Event/PositiveEvents/MedKit.h"

Cell :: Cell() : Cell(Type::PASSABLE) {}

Cell :: Cell(Type type) : type_(type), event_(nullptr) {};

Cell :: Cell(const Cell& other) : Cell() {
    swap_values(other);
}

Cell :: Cell(Cell&& other) : Cell() {
    if(this != &other) {
        swap_values(std::move(other));
    }
}

Cell& Cell :: operator=(const Cell& other) {
    if(this != &other) {
        swap_values(other);
    }
    return *this;
}

Cell& Cell :: operator=(Cell&& other) {
    if(this != &other) {
        swap_values(std::move(other));
    }
    return *this;
}

void Cell :: set_type(Type new_type) {
    type_ = new_type;
}

bool Cell :: is_entrance() const {
    return type_ == Type::ENTRANCE;
}

bool Cell :: is_exit() const {
    return type_ == Type::EXIT;
}

bool Cell :: is_passable() const {
    return type_ != Type::WALL;
}

bool Cell :: is_wall() const {
    return type_ == Type::WALL;
}

void Cell :: swap_values(const Cell& other) {
	type_ = other.type_;
	remove_event();
	add_event(other.event_ == nullptr ? nullptr : other.event_->copy());
}

void Cell :: swap_values(Cell&& other) {
    std::swap(type_, other.type_);
    remove_event();
    add_event(other.event_);
    other.event_ = nullptr;
}

[[nodiscard]] const EventInterface* Cell :: get_event() const {
    return event_;
}

void Cell :: add_event(EventInterface* event) {
    remove_event();
    event_ = event;
}

void Cell :: remove_event() {
    if(event_ != nullptr) {
        delete event_;
        event_ = nullptr;
    }
}

std::ostream &operator<<(std::ostream &out, const Cell &cell) {
    if(cell.is_entrance()) out << "[0]";
    else if(cell.is_exit()) out << "[.]";
    else if(cell.is_wall()) out << "[■]";
    else {
        auto *active_event = cell.get_event();
        if(active_event == nullptr) out << "[ ]";
        else if(const auto *ptr = dynamic_cast<const Trap*>(active_event); ptr != nullptr) out << "[-]";
        else if(const auto *ptr = dynamic_cast<const Teleport*>(active_event); ptr != nullptr) out << "[?]";
        else if(const auto *ptr = dynamic_cast<const MedKit*>(active_event); ptr != nullptr) out << "[+]";
    }
    return out;
}

Cell :: ~Cell() {
    remove_event();
}