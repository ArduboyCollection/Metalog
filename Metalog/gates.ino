#define NOT 1
#define OR 2
#define AND 3
#define NOR 4
#define NAND 5
#define XOR 6
#define INPUT 7
#define LED 8

struct Comp
{
    byte id:6;
    int a:1 = false;
    int b:1 = false;
};

struct GComp
{
    int x;
    int y;
    char name [8];
    char * bitmap;
    char * bitmapAct;
    struct Comp * comp;
};

int bool_not (int a)
{
    return !a;
}

int bool_or (int a, int b)
{
    return (a || b);
}

int bool_and (int a, int b)
{
    return (a && b);
}

int bool_nor (int a, int b)
{
    return !(a || b);
}

int bool_nand (int a, int b)
{
    return !(a && b);
}

int bool_xor (int a, int b)
{
    return (a != b);
}

int bool_output (struct Gate* gate)
{
    switch (gate->id)
    {
        case NOT:
            return bool_not (gate->a);
            break;
        case OR:
            return bool_or (gate->a, gate->b);
            break;
        case AND:
            return bool_and (gate->a, gate->b);
            break;
        case NOR:
            return bool_nor (gate->a, gate->b);
            break;
        case NAND:
            return bool_nand (gate->a, gate->b);
            break;
        case XOR:
            return bool_xor (gate->a, gate->b);    
            break;
        default:
            return false;
  }
}
