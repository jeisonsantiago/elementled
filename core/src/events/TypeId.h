#ifndef TYPEID_LAME_H
#define TYPEID_LAME_H

namespace elementled {
static const uint32_t get_unique_typeid(){
    static uint32_t type = 1u;
    return type++;
}


static const uint32_t TypeID(){
    static const uint32_t type = get_unique_typeid();
    return type;
}
}

#endif // TYPEID_LAME_H
