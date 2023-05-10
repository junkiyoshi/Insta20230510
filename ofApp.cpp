#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetColor(255);
	ofSetLineWidth(2);

	auto ico_sphere = ofIcoSpherePrimitive(250, 2);
	this->base_mesh = ico_sphere.getMesh();
	this->draw_mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->draw_mesh.clear();
	this->sphere_mesh.clear();

	for (auto v : this->base_mesh.getVertices()) {

		for (int i = 0; i < 20; i++) {

			auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.00035, ofGetFrameNum() * 0.006 + i * 0.005)), 0, 1, -180, 180) * (float)DEG_TO_RAD, glm::vec3(1, 0, 0));
			auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.00035, ofGetFrameNum() * 0.006 + i * 0.005)), 0, 1, -180, 180) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
			auto rotation_z = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.00035, ofGetFrameNum() * 0.006 + i * 0.005)), 0, 1, -180, 180) * (float)DEG_TO_RAD, glm::vec3(0, 0, 1));
			auto vertex = glm::vec4(v, 0) * rotation_z * rotation_y * rotation_x;
			vertex.z = 0;

			this->draw_mesh.addVertex(vertex);
			if (i != 0) {

				this->draw_mesh.addIndex(this->draw_mesh.getNumVertices() - 1);
				this->draw_mesh.addIndex(this->draw_mesh.getNumVertices() - 2);
			}

			if (i == 0 || i == 19) {

				this->sphere_mesh.addVertex(vertex);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	
	this->draw_mesh.drawWireframe();

	for (auto v : this->sphere_mesh.getVertices()) {

		ofDrawSphere(v, 4);
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}