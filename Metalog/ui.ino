void draw_circuit() {
    const byte * bitmap;
    for (unsigned i=0; i < circuit.nbcomps; ++i) {
        /*gb.display.drawRect(circuit.comps[i].x - camera.x,
                            circuit.comps[i].y - camera.y,
                            3, 3);
                            */
        switch (circuit.comps[i].comp.id)
            {
                case OR:
                    bitmap = BMOR;
                    break;
                case AND:
                    bitmap = BMAND;
                    break;
                case NOR:
                    bitmap = BMNOR;
                    break;
                case NAND:
                    bitmap = BMNAND;
                    break;
                case XOR:
                    bitmap = BMXOR;
                    break;
                case NOT:
                    bitmap = BMNOT;
                    break;
                case INP:
                    if (circuit.comps[i].comp.a)
                        bitmap = BMSWITCHON;
                    else
                        bitmap = BMSWITCHOFF;
                    break;
                case LED:
                    if (circuit.comps[i].comp.a)
                        bitmap = BMLEDON;
                    else 
                        bitmap = BMLEDOFF;
                    break;
                default:
                    continue;
            }    
            gb.display.drawBitmap(
                    circuit.comps[i].x - camera.x,
                    circuit.comps[i].y - camera.y,
                    bitmap);
    }
}

void draw_ui() {
    gb.display.drawBitmap(
            LCDWIDTH/2 - 2,
            LCDHEIGHT/2 - 2,
            BMCURS);
}

void get_inputs() {
    // Camera movements
    if (gb.buttons.repeat(BTN_UP, CAMERA_SPEED))
        camera.y -= 1;
    if (gb.buttons.repeat(BTN_DOWN, CAMERA_SPEED))
        camera.y += 1;
    if (gb.buttons.repeat(BTN_LEFT, CAMERA_SPEED))
        camera.x -= 1;
    if (gb.buttons.repeat(BTN_RIGHT, CAMERA_SPEED))
        camera.x += 1;

    // Camera position clamping
    camera.x = max(-(LCDWIDTH/2), camera.x);
    camera.y = max(-(LCDHEIGHT/2), camera.y);
    
}

bool placing_mode;
struct Comp * pin_wire;
void place_wire(){
    if (!placing_mode)
    {
        for (int i = 0; i < 64; ++i) 
        {
            if (gb.collidePointRect(camera.x + LCDWIDTH/2,
                        camera.y + LCDHEIGHT/2,
                        circuit.comps[i].x, circuit.comps[i].y,
                        16,16))
            {
                if (gb.collidePointRect(camera.x + LCDWIDTH/2,
                            camera.y + LCDHEIGHT/2,
                            circuit.comps[i].x, circuit.comps[i].y,
                            16,8))
                {//a
                    pin_wire = circuit.comps[i].comp.pr_a;
                }
                if (gb.collidePointRect(camera.x + LCDWIDTH/2,
                            camera.y + LCDHEIGHT/2,
                            circuit.comps[i].x, circuit.comps[i].y + 8,
                            16,8))
                {//b
                    pin_wire = circuit.comps[i].comp.pr_b;
                }
                placing_mode = true;   
                break;
            }
        }   
    }
    else
    {
        for (int i = 0; i < 64; ++i) 
        {
            if (gb.collidePointRect(camera.x + LCDWIDTH/2,
                        camera.y + LCDHEIGHT/2,
                        circuit.comps[i].x, circuit.comps[i].y,
                        16,16))
            {
                * pin_wire = circuit.comps[i].comp;
                placing_mode = false;
            }

        }
    }
}