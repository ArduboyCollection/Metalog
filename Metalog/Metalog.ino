#include <EEPROM.h>
#include <SPI.h>
#include <Gamebuino.h>

#define NULLCOMP 0
#define NOT 1
#define OR 2
#define AND 3
#define NOR 4
#define NAND 5
#define XOR 6
#define INP 7
#define LED 8
#define WIRE 9
#define HAND 10
#define PLIERS 11
#define MAXCOMP 32
#define MAXOUTP 16
#define MENUW 4
#define MENUH 3
#define CAMERA_SPEED 1

const byte BMAND[] PROGMEM = {16,16,0x0,0x0,0x0,0x0,0x0,0x0,0x1F,0xF8,0x10,0x8,0xF3,0x8,0x14,0x88,0x13,0x8,0x14,0xCF,0x14,0x88,0xF3,0x48,0x10,0x8,0x1F,0xF8,0x0,0x0,0x0,0x0,0x0,0x0,};
const byte BMLEDOFF[] PROGMEM = {16,16,0x0,0x0,0x0,0x0,0x0,0x0,0xF,0xF0,0x1F,0xF8,0x1C,0x38,0x18,0x18,0x18,0x18,0xF8,0x1F,0x18,0x18,0x1C,0x38,0x1F,0xF8,0xF,0xF0,0x0,0x0,0x0,0x0,0x0,0x0,};
const byte BMLEDON[] PROGMEM = {16,16,0x0,0x0,0x0,0x0,0x0,0x0,0xF,0xF0,0x1F,0xF8,0x1F,0xF8,0x1F,0xF8,0x1F,0xF8,0xFF,0xFF,0x1F,0xF8,0x1F,0xF8,0x1F,0xF8,0xF,0xF0,0x0,0x0,0x0,0x0,0x0,0x0,};
const byte BMNAND[] PROGMEM = {16,16,0x0,0x0,0x0,0x0,0x0,0x0,0x1F,0xF8,0x10,0x8,0xF3,0x8,0x14,0x8C,0x13,0xA,0x14,0xCF,0x14,0x88,0xF3,0x48,0x10,0x8,0x1F,0xF8,0x0,0x0,0x0,0x0,0x0,0x0,};
const byte BMNOR[] PROGMEM = {16,16,0x0,0x0,0x0,0x0,0x0,0x0,0x1F,0xF8,0x10,0x8,0xF6,0x28,0x13,0x6C,0x16,0x2A,0x10,0x2F,0x17,0x28,0xF0,0x8,0x10,0x8,0x1F,0xF8,0x0,0x0,0x0,0x0,0x0,0x0,};
const byte BMNOT[] PROGMEM = {16,16,0x0,0x0,0x0,0x0,0x0,0x0,0x1F,0xF8,0x10,0x8,0x10,0x88,0x11,0x8C,0x10,0x8A,0xF0,0x8F,0x10,0x88,0x10,0x8,0x10,0x8,0x1F,0xF8,0x0,0x0,0x0,0x0,0x0,0x0,};
const byte BMOR[] PROGMEM = {16,16,0x0,0x0,0x0,0x0,0x0,0x0,0x1F,0xF8,0x10,0x8,0xF6,0x28,0x13,0x68,0x16,0x28,0x10,0x2F,0x17,0x28,0xF0,0x8,0x10,0x8,0x1F,0xF8,0x0,0x0,0x0,0x0,0x0,0x0,};
const byte BMSWITCHOFF[] PROGMEM = {16,16,0x0,0x0,0x0,0x0,0x0,0x0,0x1F,0xF8,0x10,0x48,0x10,0xC8,0x10,0x48,0x16,0x48,0x16,0xF,0x16,0xE8,0x16,0xA8,0x16,0xE8,0x1F,0xF8,0x6,0x0,0x0,0x0,0x0,0x0,};
const byte BMSWITCHON[] PROGMEM = {16,16,0x0,0x0,0x0,0x0,0x6,0x0,0x1F,0xF8,0x16,0x48,0x16,0xC8,0x16,0x48,0x16,0x48,0x10,0xF,0x10,0xE8,0x10,0xA8,0x10,0xE8,0x1F,0xF8,0x0,0x0,0x0,0x0,0x0,0x0,};
const byte BMXOR[] PROGMEM = {16,16,0x0,0x0,0x0,0x0,0x0,0x0,0x1F,0xF8,0x10,0x8,0xF0,0x28,0x10,0x68,0x17,0x28,0x10,0x2F,0x17,0x28,0xF0,0x8,0x10,0x8,0x1F,0xF8,0x0,0x0,0x0,0x0,0x0,0x0,};
const byte BMCURS[] PROGMEM = {8,4,0x60,0x90,0x90,0x60,};
const byte BMHAND[] PROGMEM = {16,16,0x0,0x0,0xE,0x0,0xA,0x0,0xB,0xE0,0xA,0xA0,0xA,0xA0,0x3A,0xA0,0x28,0x30,0x28,0x10,0x28,0x10,0x28,0x10,0x20,0x30,0x38,0x60,0xF,0xC0,0xF,0xC0,0x0,0x0,};
const byte BMPLIERS[] PROGMEM = {16,16,0x0,0x0,0x0,0x0,0xC,0x0,0xE,0x0,0x27,0x0,0x33,0xC0,0x1F,0xFC,0xE,0x7E,0x6,0x1E,0x7,0x6,0x3,0x0,0x3,0x80,0x3,0x80,0x3,0xC0,0x1,0xC0,0x0,0x0,};
const byte BMWIRE[] PROGMEM = {16,16,0x0,0x0,0x0,0x2,0x0,0x6,0xF,0xF6,0x18,0x1E,0x37,0xCE,0x2C,0x6E,0x28,0x2C,0x28,0x2C,0x28,0x2C,0x2C,0x68,0x37,0xD8,0x18,0x30,0xF,0xE0,0x0,0x0,0x0,0x0,};

struct Comp
{
    byte id = NULLCOMP;
    bool a = false;
    bool b = false;
    struct Comp * pr_a = NULL;
    struct Comp * pr_b = NULL;
    int x;
    int y;
    char name [8];
};

struct Circuit
{
    char name [8];
    byte nbcomps = 0;
    struct Comp comps[MAXCOMP] = {NULLCOMP};
    struct Comp * outputs [MAXOUTP] = {NULL};
};

struct Save
{
    struct Circuit circuits[8];
};

struct Camera
{
    int x = 0;
    int y = 0;
};

byte menu_arr[MENUH][MENUW] = {
    {NOT,OR,AND,NOR},
    {NAND,XOR,INP,LED},
    {WIRE,HAND,PLIERS,NULLCOMP}
};
struct Circuit circuit;
struct Comp comp;

Camera camera;

Gamebuino gb;

void setup() {
    Serial.begin(9600);
    gb.begin();
    gb.titleScreen(F("Metalog"));
    circuit.comps[0].id = INP;
    circuit.comps[0].x = 3;
    circuit.comps[0].y = 5;
    circuit.comps[0].a = true;
    circuit.comps[3].id = INP;
    circuit.comps[3].a = true;
    circuit.comps[3].x = 3;
    circuit.comps[3].y = 23;
    circuit.comps[1].id = AND;
    circuit.comps[1].x = 20;
    circuit.comps[1].y = 10;
    circuit.comps[1].pr_a = &circuit.comps[0];
    circuit.comps[1].pr_b = &circuit.comps[3];
    circuit.comps[4].id = LED;
    circuit.comps[4].x = 40;
    circuit.comps[4].y = 10;
    circuit.comps[4].pr_a = &circuit.comps[1];
    circuit.outputs[0] = &circuit.comps[4];
    circuit.nbcomps = 5;
    update_outputs(circuit.outputs);
}

void loop() {
    if (gb.update()){
        get_inputs();
        // update_logic();
        draw_circuit();
        draw_ui();
    }
}
