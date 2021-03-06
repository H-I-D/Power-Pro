#include "tank.h"

void initSelect(void)
{
    int i;
    /* variables
     ----------------------*/
    score = 0;
    time_count = 0;
    stages[0].selected = 1;
    for (i = 0; i < STAGE_MAX; i++) {
        stages[i].level = i + 1;
        stages[i].x = (i+1) * 10;
        if (i < 2) stages[i].x -= 2;
        stages[i].y = 20;
    }
    strncpy(stages[0].name, "easy", 4);
    strncpy(stages[1].name, "normal", 6);
    strncpy(stages[2].name, "hard", 4);
    
    /* ------------------ */
    glClearColor(1.0, 1.0, 1.0, 1.0);  // background color
    glutKeyboardFunc(selectKeyboardFunc);
    glutSpecialFunc(selectSpecialFunc);
    glutIdleFunc(idle);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120.0, 1, 0, 10);
    scoreRead();
}

void initStage(void)
{
    int i;
    srand((unsigned)time(NULL));
    /* variables
    ----------------------*/
    for (i = 0;i < kabeIndex;i++) flag_kabe[i] = 1;
    jiki.t = PI/2.0;
    jiki.w = 1.0;
    jiki.h = 2.0;
    jiki.x = 1.0;
    jiki.y = 1.0;
    jiki.v = 0.14;
    jiki.v_turn = 0.02;
    jiki.score = 1000;
    for (i = 0;i < TAMA_MAX;i++) {
        jiki.tama[i].damage = 1;
        jiki.tama[i].v = 0.35;
    }
    for (i = 0;i < TEKI_MAX; i++) {
        teki[i].v_turn = 0.03;
        teki[i].t = rand();
        teki[i].w = 1.0;
        teki[i].h = 2.0;
    }
    /*--------------------*/
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    glutKeyboardFunc(stageKeyboardFunc);
    glutSpecialFunc(stageSpecialFunc);
    glutSpecialUpFunc(stageSpecialUpFunc);
    
    glutIdleFunc(idle);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0, 1, .1, 70.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, -10.0, 4.0, 0.0, 0.0, 1.5, 0.0, 0.0, 1.0);
    glLightfv(GL_LIGHT1, GL_POSITION, pos1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, color[WHITE]);
    switch (current_status) {
        case 1: initEasy(); break;
        case 2: initNormal(); break;
        case 3: initHard(); break;
    }
    for (i = 0;i < POWERUP_MAX;i++)
        powerupTimerFunc(i);
    timeCount(0);
}

void initEasy(void)
{
    int i, j;
	for (i = 0;i < X + 1;i++)
	{
		kabeList[i][0] = -0.5 + i;
		kabeList[i][1] = -0.5;
		kabeList[i][2] = 0.5;
	}
	for (i = 0;i < Y + 1;i++)
	{
		kabeList[i + X + 1][0] = X + 0.5;
		kabeList[i + X + 1][1] = i - 0.5;
		kabeList[i + X + 1][2] = 0.5;
	}
	for (i = 0;i < X + 1;i++)
	{
		kabeList[i + X + Y + 2][0] = X + 0.5 - i;
		kabeList[i + X + Y + 2][1] = Y + 0.5;
		kabeList[i + X + Y + 2][2] = 0.5;
	}
	for (i = 0;i < Y + 1;i++)
	{
		kabeList[i + X + X + Y + 3][0] = -0.5;
		kabeList[i + X + X + Y + 3][1] = Y + 0.5 - i;
		kabeList[i + X + X + Y + 3][2] = 0.5;
	}
	for (i = 0;i < 7;i++)
	{
		kabeList[i + X + X + Y + Y + 4][0] = 12.5;
		kabeList[i + X + X + Y + Y + 4][1] = 3.5 + i;
		kabeList[i + X + X + Y + Y + 4][2] = 0.5;
	}
	for (i = 0;i < 7;i++)
	{
		kabeList[i + X + X + Y + Y + 11][0] = 3.5 + i;
		kabeList[i + X + X + Y + Y + 11][1] = 12.5;
		kabeList[i + X + X + Y + Y + 11][2] = 0.5;
	}
	for (i = 0;i < 13;i++)
	{
		kabeList[i + 2 * (X + Y) + 18][0] = 3.5 + i;
		kabeList[i + 2 * (X + Y) + 18][1] = Y / 2;
		kabeList[i + 2 * (X + Y) + 18][2] = 0.5;
	}
	for (i = 0;i < 13;i++)
	{
		kabeList[i + 2 * (X + Y) + 31][0] = 19.5 + i;
		kabeList[i + 2 * (X + Y) + 31][1] = Y / 2;
		kabeList[i + 2 * (X + Y) + 31][2] = 0.5;
	}
	for (i = 0;i < 13;i++)
	{
		kabeList[i + 2 * (X + Y) + 44][0] = 35.5 + i;
		kabeList[i + 2 * (X + Y) + 44][1] = Y / 2;
		kabeList[i + 2 * (X + Y) + 44][2] = 0.5;
	}
	for (i = 0;i < 7;i++)
	{
		kabeList[i + X + X + Y + Y + 57][0] = 12.5;
		kabeList[i + X + X + Y + Y + 57][1] = Y-(3.5 + i);
		kabeList[i + X + X + Y + Y + 57][2] = 0.5;
	}
	for (i = 0;i < 7;i++)
	{
		kabeList[i + X + X + Y + Y + 64][0] = 3.5 + i;
		kabeList[i + X + X + Y + Y + 64][1] = Y-12.5;
		kabeList[i + X + X + Y + Y + 64][2] = 0.5;
	}
	for (i = 0;i < 7;i++)
	{
		kabeList[i + X + X + Y + Y + 71][0] = X-12.5;
		kabeList[i + X + X + Y + Y + 71][1] = 3.5 + i;
		kabeList[i + X + X + Y + Y + 71][2] = 0.5;
	}
	for (i = 0;i < 7;i++)
	{
		kabeList[i + X + X + Y + Y + 78][0] = X-(3.5 + i);
		kabeList[i + X + X + Y + Y + 78][1] = 12.5;
		kabeList[i + X + X + Y + Y + 78][2] = 0.5;
	}
	for (i = 0;i < 7;i++)
	{
		kabeList[i + X + X + Y + Y + 85][0] = X-12.5;
		kabeList[i + X + X + Y + Y + 85][1] = Y-(3.5 + i);
		kabeList[i + X + X + Y + Y + 85][2] = 0.5;
	}
	for (i = 0;i < 7;i++)
	{
		kabeList[i + X + X + Y + Y + 92][0] = X-(3.5 + i);
		kabeList[i + X + X + Y + Y + 92][1] = Y-12.5;
		kabeList[i + X + X + Y + Y + 92][2] = 0.5;
	}
	kabeIndex = X + X + Y + Y + 99;

	for (i = 0;i < kabeIndex;i++) flag_kabe[i] = 1;
	TEKI_MAX = 3;

    jiki.life = 50;
	jiki.w = 1.0;
	jiki.h = 2.0;
    for (i = 0; i < TAMA_MAX; i++) {
        jiki.tama[i].r = 0.5;
    }

    teki[0].x = X*3.0 / 4.0;
    teki[0].y = Y*3.0 / 4.0;
    teki[1].x = X / 4.0;
    teki[1].y = Y / 4.0;
    teki[1].t = 0;
    teki[2].x = X * 3.0 / 4.0;
    teki[2].y = Y / 4.0;
    teki[2].t = -PI/4;
    for (j = 0;j < TEKI_MAX;j++)
    {
        teki[j].life = 3;
        teki[j].w = 1.5;
		teki[j].h = 2.0;
        teki[j].v = 0.1;
        for (i = 0;i < TAMA_MAX; i++) {
            teki[j].tama[i].v = 0.166;
            teki[j].tama[i].damage = 1;
            teki[j].tama[i].r = 0.3;
        }
    }
    
    for (i = 0;i < POWERUP_MAX;i++) {
        powerups[i].x = 10;
        powerups[i].y =  5 + i*15;
        powerups[i].flag = 1;
        powerups[i].type = 2;
    }
    powerups[0].x = 45;
    powerups[0].y = 5;
    powerups[0].type = 1;
    
    jikiTimerFunc(0);
    teki[0].score = teki_scores[0];
    teki[1].score = teki_scores[1];
    teki[2].score = teki_scores[4];
    teki0TimerFunc(0);
    teki1TimerFunc(1);
    teki4TimerFunc(2);
}

void initNormal(void)
{
    int i, j;
	for (i = 0;i < X + 1;i++)
	{
		kabeList[i][0] = -0.5 + i;
		kabeList[i][1] = -0.5;
		kabeList[i][2] = 0.5;
	}
	for (i = 0;i < Y + 1;i++)
	{
		kabeList[i + X + 1][0] = X + 0.5;
		kabeList[i + X + 1][1] = i - 0.5;
		kabeList[i + X + 1][2] = 0.5;
	}
	for (i = 0;i < X + 1;i++)
	{
		kabeList[i + X + Y + 2][0] = X + 0.5 - i;
		kabeList[i + X + Y + 2][1] = Y + 0.5;
		kabeList[i + X + Y + 2][2] = 0.5;
	}
	for (i = 0;i < Y + 1;i++)
	{
		kabeList[i + X + X + Y + 3][0] = -0.5;
		kabeList[i + X + X + Y + 3][1] = Y + 0.5 - i;
		kabeList[i + X + X + Y + 3][2] = 0.5;
	}
	for(i=0;i<32;i++)
	{
		kabeList[i+X+X+Y+Y+4][0]=9.5+i;
		kabeList[i+X+X+Y+Y+4][1]=4.5;
		kabeList[i+X+X+Y+Y+4][2]=0.5;
	}
	for(i=0;i<32;i++)
	{
		kabeList[i+X+X+Y+Y+36][0]=4.5;
		kabeList[i+X+X+Y+Y+36][1]=9.5+i;
		kabeList[i+X+X+Y+Y+36][2]=0.5;
	}
	for(i=0;i<32;i++)
	{
		kabeList[i+X+X+Y+Y+68][0]=X-4.5;
		kabeList[i+X+X+Y+Y+68][1]=9.5+i;
		kabeList[i+X+X+Y+Y+68][2]=0.5;
	}
	for(i=0;i<32;i++)
	{
		kabeList[i+X+X+Y+Y+100][0]=9.5+i;
		kabeList[i+X+X+Y+Y+100][1]=Y-4.5;
		kabeList[i+X+X+Y+Y+100][2]=0.5;
	}
	kabeIndex=2*(X+Y)+132;
	for(i=0;i<kabeIndex;i++) flag_kabe[i]=1;
	TEKI_MAX=3;
    jiki.life = 10;
    for (i = 0; i < TAMA_MAX; i++) {
        jiki.tama[i].r = 0.3;
    }
    
    teki[0].x = X / 2.0;
    teki[0].y = Y / 2.0;
    teki[1].x = X / 4.0;
    teki[1].y = Y / 4.0;
    teki[2].x = X * 3.0 / 4.0;
    teki[2].y = Y / 4.0;
    
    for (j = 0;j < TEKI_MAX;j++)
    {
        teki[j].life = 5;
        teki[j].w = 1.0;
		teki[j].h=2.0;
        teki[j].v = 0.07;
        for (i = 0;i < TAMA_MAX; i++) {
            teki[j].tama[i].v = 0.2;
            teki[j].tama[i].damage = 1;
            teki[j].tama[i].r = 0.3;
        }
    }
    
    for (i = 0;i < POWERUP_MAX;i++) {
        powerups[i].x = 10;
        powerups[i].y =  7 + i*15;
        powerups[i].flag = 1;
        powerups[i].type = i;
    }
    powerups[1].type = 2;
    
    jikiTimerFunc(0);
    teki[0].score = teki_scores[0];
    teki[1].score = teki_scores[1];
    teki[2].score = teki_scores[4];
    teki0TimerFunc(0);
    teki1TimerFunc(1);
    teki4TimerFunc(2);
}

void initHard(void)
{
    int i, j;
	for (i = 0;i < X + 1;i++)
	{
		kabeList[i][0] = -0.5 + i;
		kabeList[i][1] = -0.5;
		kabeList[i][2] = 0.5;
	}
	for (i = 0;i < Y + 1;i++)
	{
		kabeList[i + X + 1][0] = X + 0.5;
		kabeList[i + X + 1][1] = i - 0.5;
		kabeList[i + X + 1][2] = 0.5;
	}
	for (i = 0;i < X + 1;i++)
	{
		kabeList[i + X + Y + 2][0] = X + 0.5 - i;
		kabeList[i + X + Y + 2][1] = Y + 0.5;
		kabeList[i + X + Y + 2][2] = 0.5;
	}
	for (i = 0;i < Y + 1;i++)
	{
		kabeList[i + X + X + Y + 3][0] = -0.5;
		kabeList[i + X + X + Y + 3][1] = Y + 0.5 - i;
		kabeList[i + X + X + Y + 3][2] = 0.5;
	}
	kabeIndex=X+X+Y+Y+4;
	for(i=0;i < kabeIndex;i++) flag_kabe[i]=1;
	TEKI_MAX=3;
    jiki.life = 10;
    for (i = 0; i < TAMA_MAX; i++) {
        jiki.tama[i].r = 0.3;
    }
    
    teki[0].x = X / 2.0;
    teki[0].y = Y / 2.0;
    teki[1].x = X / 4.0;
    teki[1].y = Y / 4.0;
    teki[2].x = X * 3.0 / 4.0;
    teki[2].y = Y / 4.0;
    
    for (j = 0;j < TEKI_MAX;j++)
    {
        teki[j].life = 10;
        teki[j].w = 1.0;
        teki[j].v = 0.1;
        for (i = 0;i < TAMA_MAX; i++) {
            teki[j].tama[i].v = 0.4;
            teki[j].tama[i].damage = 2;
            teki[j].tama[i].r = 0.3;
        }
    }
    
    for (i = 0;i < POWERUP_MAX;i++) {
        powerups[i].x = 10;
        powerups[i].y =  5 + i*15;
        powerups[i].flag = 1;
        powerups[i].type = i;
    }
    
    jikiTimerFunc(0);
    teki[0].score = teki_scores[0];
    teki[1].score = teki_scores[1];
    teki[2].score = teki_scores[2];
    teki0TimerFunc(0);
    teki1TimerFunc(1);
    teki2TimerFunc(2);
}

void initResult(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);  // background color
    glutKeyboardFunc(resultKeyboardFunc);
    glutIdleFunc(idle);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120.0, 1, 0, 10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
}
