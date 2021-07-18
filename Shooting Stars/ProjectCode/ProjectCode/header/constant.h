#ifndef ARCADESHOOTER_CONSTANT_H
#define ARCADESHOOTER_CONSTANT_H

static int LIFE_LEFT = 5;//done
static int PLAYER_FIRE_CALLED = 0; //done

static int GAME_SCORE = 0;
static int count = 0;
static int firehasCalled = 0;
static int fireIsActive = 0;
static int score;
static char life_level[10];
static char score_count[10];
static char flag_beche_ase[10];
static int bullet_hit_by_fire;

static int bulletRowPosition; // done

static int bulletColPosition; //done

static int playerRowPosition, playerColPosition; //done

static int fireColPosition, fireRowPosition; //done
static int enemyPosition;

const static char col_position0[] = {0b11100000, 0b01110000, 0b00111000,0b00011100,0b00001110,0b00000111,0b00000000, 0b00000000,
0b00000000, 0b00000000,0b00000000,0b00000000};
const static char col_position1[] = {0b00000000, 0b00000000, 0b00000000,0b00000000,0b00000000,0b00000000,0b11100000, 0b01110000,
0b00111000,0b00011100,0b00001110,0b00000111};

const char columns [] ={0b00000001,0b000000010, 0b00000100,0b00001000,0b00010000,0b00100000,0b01000000,0b10000000, 0b00000001,0b000000010,
0b00000100,0b00001000,0b00010000, 0b00100000,0b01000000,0b10000000};	//done

const static char row_position0[] = {0b00000000, 0b00001000, 0b00010000, 0b00011000, 0b00100000, 0b00101000, 0b00110000, 0b00111000};//done

const static char row_position1[] = {0b00000001, 0b00001001, 0b00010001, 0b00011001, 0b00100001, 0b00101001, 0b00110001, 0b00111001};//done

const static char row_position2[] = {0b00000010, 0b00001010, 0b00010010, 0b00011010, 0b00100010, 0b00101010, 0b00110010, 0b00111010};//done

const static char row_position3[] = {0b00000011, 0b00001011, 0b00010011, 0b00011011, 0b00100011, 0b00101011, 0b00110011, 0b00111011};//done

static char rowcode;		//done
static char columncode;		//done


#endif