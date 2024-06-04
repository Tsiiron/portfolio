#ifndef cell_h
#define cell_h

#include "Event/Interface/EventInterface.h"
#include <ostream>

class Cell {
public:
    enum Type {ENTRANCE, EXIT, PASSABLE, WALL};

private:
    Type type_;
    EventInterface* event_;

    void swap_values(const Cell& other);
    void swap_values(Cell&& other);

public:
    Cell();
    Cell(Type type);
    Cell(const Cell& other);
    Cell(Cell&& other);
    
    Cell& operator= (const Cell &other);
    Cell& operator= (Cell &&other);
    
    void set_type(Type new_type);

    bool is_entrance() const;
    bool is_exit() const;
    bool is_passable() const;
    bool is_wall() const;

    [[nodiscard]] const EventInterface* get_event() const;
    void add_event(EventInterface* event);
    void remove_event();

    friend std::ostream &operator<<(std::ostream &out, const Cell &cell);

    ~Cell();
};

#endif