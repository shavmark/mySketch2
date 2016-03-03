#pragma once
#include "2552software.h"
#include "ofxBox2d.h"
#include "ofxBox2dParticleSystem.h"

namespace Software2552 {
	class Text;
	class Character;

	class Particles : public ofxBox2dParticleSystem {
	public:
		ofxBox2dParticleSystem particles;			      //    LiquidFun particle system
		void draw(int x, int y) {
			particles.setPosition(x, y);
			particles.draw();
			ofBackgroundGradient(ofColor(0), ofColor(63), OF_GRADIENT_LINEAR);
			ofFill();
			ofEnableBlendMode(OF_BLENDMODE_ADD);
			ofEnableBlendMode(OF_BLENDMODE_ALPHA);
			franklinBook14.drawStringAsShapes("Known years native people were in MN before first treaty (12,000)", 15, 480);
		}
		void update() {
			years += 10;
			if (years < 12000) {
				for (int i = 0; i < 10; i++) {
					float radius = ofRandom(160, 280);
					ofVec2f position = ofVec2f(cos(ofRandom(PI * 2.0)), sin(ofRandom(PI * 2.0)));
					ofVec2f velocity = ofVec2f(0.0f, -50.0f);
					ofColor color;
					int hue = int(ofGetFrameNum() / 4.0) % 255;
					color.setHsb(hue, 180, 255);
					particles.setColor(color);
					particles.setParticleFlag(b2_elasticParticle);
					particles.createParticle(position, velocity);
					if (years < 12000) {
						years += 10;
					}
				}


			}
			box2d.update();
		}
		void setup(){
			box2d.init();
			box2d.setGravity(0, 0);
			box2d.setFPS(30.0);
			box2d.createBounds();
			years = 0;
			ofColor color;
			color.set(255);
			particles.setParticleFlag(b2_tensileParticle);
			particles.loadImage("particle32.png");
			particles.setup(box2d.getWorld(), 12000, 160.0, 16.0, 92.0, ofColor(0, 0, ofRandom(128, 255)));

		}
		int years;
		ofTrueTypeFont  franklinBook14;
		ofxBox2d box2d;
		vector <ofPtr<ofxBox2dCircle> >	circles;		  //	default box2d circles
		vector <ofPtr<ofxBox2dRect> > boxes;			  //	defalut box2d rects

	};
	
	class CharacterEngine {
	public:
		CharacterEngine() {}
		void draw(Character*) {};
		void update() {};

	private:
	};

	class TextEngine {
	public:
		TextEngine() {}
		void draw(Text*);
		void update() {};

	private:
	};

}