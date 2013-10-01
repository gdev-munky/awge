#ifndef _RES_H_
#define _RES_H_

#include "ofMain.h"
#include "animation.h"

#define MAX_GFX	20
#define MAX_SFX	10
#define MAX_ANI	10

class ResStore
{
public:
	int gfx_count;
	int ani_count;
	int sfx_count;

	ofImage gfx[MAX_GFX];
	ofImage gfx_m[MAX_GFX];
	AnimatedSequence gfx_a[MAX_ANI];	

	ofSoundPlayer sfx[MAX_SFX];

	ResStore(){}
	~ResStore(){}

	int precacheGFX(string fname, bool mV, bool mH)
	{
		ofImage img = ofImage(fname);
		ofImage img2 = ofImage(fname);
		img2.mirror(mV, mH);

		gfx[gfx_count] = img;
		gfx_m[gfx_count] = 	img2;
		gfx_count++;
		return gfx_count - 1;
	}

	int precacheANI(string fname0, string fname1, int c)
	{
		gfx_a[ani_count] = AnimatedSequence(fname0, fname1, c);
		ani_count++;
		return ani_count - 1;
	}

	int precacheSFX(string fname)
	{
		ofSoundPlayer sp = ofSoundPlayer();
		sp.loadSound(fname);
		sp.setVolume(1.0f);
		sfx[sfx_count] = sp;
		sfx_count++;
		return sfx_count - 1;
	}
};

extern ResStore rStore;
//Статичная текстура индекса i
#define GFXN(i) (rStore.gfx[i])

//Статичная отраженная текстура индекса i
#define GFXM(i) (rStore.gfx_m[i])

//Анимация индекса i
#define GFXA(i) (rStore.gfx_a[i])

//звук индекса i
#define SFX(i) (rStore.sfx[i])

//GFX------------------------------------------------------------
extern  int iModelPlayer;
extern  int iModelWpnAKS74U;
extern  int iModelBackGround;
//GFX - MONSTERS
extern  int iModelMonsterGay;
extern int iAnimMonsterSlimeGreenMove;
extern int iAnimMonsterSlimeGreenDie;
extern int iAnimMonsterSlimeGoldMove;
extern int iAnimMonsterSlimeGoldDie;
extern int iAnimMonsterSlimeBlueMove;
extern int iAnimMonsterSlimeBlueDie;

//SFX-----------------------------------------------------------
extern  int iSfxMainTheme;
extern  int iSfxBulletHit;
extern  int iSfxWalkDirt;

#endif
