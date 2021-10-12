#ifndef HANDLER_H
#define HANDLER_H

#include "geometry.h"
#include <vector>
class Operation{
    std::vector<VectorObject*> results;
private:
    std::vector<coord_t> options;
    virtual void to_do(coord_t args ...);
    virtual void undo(coord_t args ...);
};

#endif // HANDLER_H
