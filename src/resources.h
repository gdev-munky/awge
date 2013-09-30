#ifndef _RES_H_
#define _RES_H_

#include "ofMain.h"
#include "animation.h"

class ResStore
{
public:
	int gfx_count;
	int ani_count;
	int sfx_count;

	vector<ofImage*> gfx;
	vector<ofImage*> gfx_m;
	vector<AnimatedSequence*> gfx_a;	

	vector<ofSoundPlayer*> sfx;

	ResStore(){}
	~ResStore(){}

	int precacheGFX(string fname, bool mV, bool mH)
	{
		ofImage img = ofImage(fname);
		ofImage img2 = ofImage(fname);
		img2.mirror(mV, mH);

		gfx.push_back(		&img	);
		gfx_m.push_back(	&img2	);
		gfx_count++;
		return gfx_count - 1;
	}

	int precacheANI(string fname0, string fname1, int c)
	{
		gfx_a.push_back(&AnimatedSequence(fname0, fname1, c));
		ani_count++;
		return ani_count - 1;
	}

	int precacheSFX(string fname)
	{
		ofSoundPlayer sp = ofSoundPlayer();
		sp.loadSound(fname);
		sfx.push_back(&sp);
		sfx_count++;
		return sfx_count - 1;
	}
};

static ResStore rStore;
//”казатель на статичную текстуру индекса i
#define GFXN(i) rStore.gfx[i]

//”казатель на статичную отраженную текстуру индекса i
#define GFXM(i) rStore.gfx_m[i]

//”казатель на анимацию индекса i
#define GFXA(i) rStore.gfx_a[i]

//”казатель на звук индекса i
#define SFX(i) rStore.sfx[i]

//GFX------------------------------------------------------------
static int iModelPlayer;
static int iModelWpnAKS74U;
static int iModelBackGround;
//GFX - MONSTERS
static int iModelMonsterSlimeGreen;
static int iModelMonsterSlimeGold;
static int iModelMonsterSlimeBlue;
static int iModelMonsterGay;

//SFX-----------------------------------------------------------
static int iSfxMainTheme;
static int iSfxBulletHit;

#endif
