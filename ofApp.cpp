#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(3);
	ofEnableDepthTest();

	this->font_size = 350;
	this->font.loadFont("fonts/Kazesawa-Bold.ttf", this->font_size, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	auto path = font.getCharacterAsPoints('A', true, false);
	auto outline = path.getOutline();

	auto noise_seed_x = ofRandom(1000);
	auto noise_seed_y = ofRandom(1000);
	auto noise_seed_z = ofRandom(1000);

	for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

		if (outline_index != 0) { ofNextContour(true); }

		outline[outline_index] = outline[outline_index].getResampledBySpacing(15);
		auto vertices = outline[outline_index].getVertices();

		for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

			for (int i = 0; i < 25; i++) {

				ofSetColor(39, ofMap(i, 0, 15, 0, 255));

				auto location = glm::vec3(vertices[vertices_index].x - this->font.stringWidth(string{ 'A' }) * 0.5, vertices[vertices_index].y + this->font.stringHeight(string{ 'A' }) * 0.5, 0);
				auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_x, (ofGetFrameNum() + i) * 0.005), 0, 1, -PI, PI), glm::vec3(1, 0, 0));
				auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_y, (ofGetFrameNum() + i) * 0.005), 0, 1, -PI, PI), glm::vec3(0, 1, 0));
				auto rotation_z = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_z, (ofGetFrameNum() + i) * 0.005), 0, 1, -PI, PI), glm::vec3(0, 0, 1));
				location = glm::vec4(location, 0) * rotation_z * rotation_y;

				auto next_location = glm::vec3(vertices[vertices_index].x - this->font.stringWidth(string{ 'A' }) * 0.5, vertices[vertices_index].y + this->font.stringHeight(string{ 'A' }) * 0.5, 0);
				auto next_rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_x, (ofGetFrameNum() + i + 1) * 0.005), 0, 1, -PI, PI), glm::vec3(1, 0, 0));
				auto next_rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_y, (ofGetFrameNum() + i + 1) * 0.005), 0, 1, -PI, PI), glm::vec3(0, 1, 0));
				auto next_rotation_z = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_z, (ofGetFrameNum() + i + 1) * 0.005), 0, 1, -PI, PI), glm::vec3(0, 0, 1));
				next_location = glm::vec4(next_location, 0) * next_rotation_z * next_rotation_y;

				ofDrawLine(location, next_location);

				if (i == 24) { ofDrawSphere(next_location, 3); };
			}
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}