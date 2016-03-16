#pragma once
#include "2552software.h"
#include "ofxBox2d.h"
#include "color.h"
#include "animation.h"

// home of custom drawing

namespace Software2552 {
	class Text;
	class Character;
	class Particles;
	class Video;
	class Settings;
	class Colors;

	// simple drawing 
	class Rectangle : public BaseAnimation {
	public:

		void draw();
	};

	// drawing related items start here
	class BaseClass2552WithDrawing : public BaseClass {
	public:
		BaseClass2552WithDrawing() { valid = false; }

		bool objectValid() { return valid; } // data is in a good state
		void setValid(bool b = true) { valid = b; };

	private:
		bool valid; // true when data is valid and ready to draw
	};
	class Graphics2552 {
	public:
		static void rotateToNormal(ofVec3f normal);

	};

	template<typename T>
	class Role : public Animator {
	public:
		// fill in the ones you need in derived classes
		virtual void draw(T*) {};
		virtual void update(T*) {};
		virtual void setup(T*) {};
		virtual void play() {};
		virtual void stop() {};
		virtual void pause() {};
	};

	class CrazyMesh : public ofMesh {
	public:
		CrazyMesh(const ofFloatColor&colorIn = ofFloatColor::orange) : ofMesh() { color = colorIn; }
		virtual void setup();
		virtual void update();
		virtual void draw();
	private:
		ofFloatColor color;
		int w = 200;
		int h = 200;
	};

	// basic mesh stuff for learning
	class MeshEngine : public ofMesh {
	public:
		void setup();
	private:
	};

	//http://openframeworks.cc/ofBook/chapters/generativemesh.html
	class MoreMesh : public MeshEngine {
	public:
		void setup();
		void draw();
	private:
		ofImage		image;
		ofEasyCam	easyCam;
		ofLight		light;

	};


	class Primitive : public Animator {
	public:
		void setWireframe(bool b = true) { wireFrame = b; }
		bool useWireframe() { return wireFrame; }
	private:
		bool wireFrame = true;

	};
	class Plane : public ofPlanePrimitive, public Primitive {
	public:
		void draw() {
			if (useWireframe()) {
				drawWireframe();
			}
			else {
				ofPlanePrimitive::draw();
			}
		}
	}; 
	class Cube : public ofBoxPrimitive, public Primitive {
	public:
		void draw() {
			if (useWireframe()) {
				drawWireframe();
			}
			else {
				ofBoxPrimitive::draw();
			}
		}
	}; 
	class Sphere : public ofSpherePrimitive, public Primitive {
	public:
		void draw() {
			if (useWireframe()) {
				drawWireframe();
			}
			else {
				ofSpherePrimitive::draw();
			}
			//drawFaces();
			//drawVertices();
		}

	private:
	};
	class VectorPattern : public Animator {
	public:
		void matrix(int twistx, int shifty) {
			ofPushMatrix();
			for (int i = -50; i < 50; ++i) {
				ofTranslate(0, i*shifty);
				ofRotate(i*twistx);
				stripe(true);
			}
			ofPopMatrix();
		}
		void stripe(bool rotate=false) {
			ofSetColor(ofColor::black);
			ofSetLineWidth(3);
			for (int i = -50; i < 50; ++i) {
				ofPushMatrix();
				ofTranslate(i * 20, 0);
				if (rotate) {
					ofRotate(i * 5);
				}
				ofLine(0, -100, 0, 100);
				ofPopMatrix();
			}
		}
		void triangle(bool rotate = false) {
			ofSetColor(ofColor::black);
			ofSetLineWidth(3);
			ofNoFill();
			for (int i = -50; i < 50; ++i) {
				ofPushMatrix();
				ofTranslate(i * 20, 0);
				if (rotate) {
					ofRotate(i * 5);
				}
				ofScale(6, 6); // enlarge 6x
				ofTriangle(0, 0, -50, 100, 50, 100);
				ofPopMatrix();
			}
		}
		void shape(int twistx, int shifty, bool rect, bool fill, int rotate, int alpha=100) {
			ofColor color = ofColor::black;
			color.a = alpha;
			ofSetColor(color);
			ofSetLineWidth(1);
			if (fill) {
				ofFill();
			}
			else {
				ofNoFill();
			}
			for (int i = -50; i < 50; ++i) {
				ofPushMatrix();
				ofRotate(i * twistx);
				ofTranslate(i * 20, shifty);
				ofRotate(rotate);
				ofScale(6, 6); // enlarge 6x
				if (rect) {
					ofRect(-50, -50, 100, 100);
				}
				else {
					ofTriangle(0, 0, -50, 100, 50, 100);
				}
				ofPopMatrix();
			}
			ofScale(6, 6); // enlarge 6x
			ofTriangle(0, 0, -50, 100, 50, 100);
		}
	};
	class Camera : public ofEasyCam, public Animator {
	public:
		void orbit();
		void setOrbit(bool b = true) { useOrbit = b; }
		bool isOrbiting() const { return useOrbit; }
	private:
		bool useOrbit = false;
	};
	class Fbo : public ofFbo {
	public:
	};

	
	class Grabber : public ofVideoGrabber, public Animator {
	public:
		Grabber(const string&nameIn) :ofVideoGrabber(), Animator() { name = nameIn;  }
		void loadGrabber(int w, int h) {
			id = find();
			setDeviceID(id);
			setDesiredFrameRate(30);
			setup(w, h);
		}
		bool loadRaster() {
			return true;// ofLoadImage(*this, path);
		}
	private:
		int find() {
			//bugbug does Kintect show up?
			ofVideoGrabber grabber;
			vector<ofVideoDevice> devices = grabber.listDevices();
			for (vector<ofVideoDevice>::iterator it = devices.begin(); it != devices.end(); ++it) {
				if (it->deviceName == name) {
					return it->id;
				}
			}
		}
		string name;
		int id=0;
	};

	class Raster : public ofImage, public Animator {
	public:
		Raster(const string&pathIn) :ofImage(), Animator() { path = pathIn; }
		bool loadRaster() {
			return ofLoadImage(*this, path);
		}
	private:
		string path;
	};

	class VideoPlayer :public ofVideoPlayer, public Animator {
	public:
		VideoPlayer(const string&pathIn) :ofVideoPlayer(), Animator() { path = pathIn; }
		bool loadVideo() {
			return load(path);
		}
	private:
		string path;
	};

	class TextureVideo : public ofVideoPlayer {
	public:
		void create(const string& name, float w, float h) {
			load(name);
			play();
		}
		bool textureReady() {
			return isInitialized();
		}
		bool bind() { 
			if (isInitialized() && isUsingTexture()) {
				getTexture().bind();
				return true;
			}
			return false;
		}
		bool unbind() {
			if (isInitialized() && isUsingTexture()) {
				getTexture().unbind();
				return true;
			}
			return false;
		}
	private:

	};
	class TextureFromImage : public ofTexture {
	public:
		void setup() {
		}
		void create(const string& name, float w, float h) {
			// create texture
			ofLoadImage(*this, name);
			fbo.allocate(w,h, GL_RGB);
			fbo.begin();//fbo does drawing
			ofSetColor(ofColor::white); // no image color change when using white
			draw(0, 0, w,h);
			fbo.end();// normal drawing resumes
		}
		float getWidth() { return fbo.getWidth(); }
		float getHeight() { return fbo.getHeight(); }
		void bind() { fbo.getTextureReference().bind(); }
		void unbind() { fbo.getTextureReference().unbind(); }
		
	private:
		Fbo	fbo;

	};
	class Light : public ofLight, public Animator {
	public:
	};
	class Material : public ofMaterial {
	public:
	};
	class RoleBackground : public Role<Colors> {
	public:
		RoleBackground(){ mode = OF_GRADIENT_LINEAR; }
		void setup(Colors* color);
		void draw(Colors* color);
		void update(Colors*color);
	private:
		ofGradientMode mode;

		//ofBackgroundHex this is an option too bugbug enable background type
	};
	class RoleCharacter : public Role<Character> {
	public:

	private:
	};
	// put advanced drawing in these objects
	class RoleVideo :public ofVideoPlayer {
	public:
		void draw(Video*v);
		
	private:
	};
	class RoleText : public Role<Text> {
	public:
		void draw(Text*);
		static void draw(const string &s, int x, int y);

	private:
	};

}