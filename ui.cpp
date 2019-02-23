#include <managers.h>

bool flagHover = false;
bool flagClick = false;
UIManager* UI;
UIManager::UIManager(){
	UI = this;
}

void UIManager::updateUI(){
	int size = UIElements.size();
	for (int i = 0; i < size; ++i){
		UIElements[i].update();
	}
	while (!(messageQueue.empty())){
		handleMessage(dispatchMessage());
	}
	for (int i = 0; i < size; ++i){
		UIElements[i].renderMe();
	}
}

UIMessage UIManager::dispatchMessage(){
	UIMessage temp = messageQueue.front();
	messageQueue.pop();
	return temp;
}

void UIManager::pushMessage(UIMessage msg){
	messageQueue.push(msg);
}

void UIManager::createElement(UIElement* element){
	UIElements.push_back(*element);
}

void UIManager::handleMessage(UIMessage msg){
	switch (msg.type){
		case buttonClick:
			switch (msg.id){
				case 23137:
					Entities->getEntities().push_back(new Enemy);
			}
	}
}

Button::Button(int x, int y, int w, int h, std::string textt, int idd){
	dimensions.x = x;
	dimensions.y = y;
	dimensions.w = w;
	dimensions.h = h;
	currTexture.second = &dimensions;
	text = textt;
	id = idd;
	type = button;
}

void Button::renderMe(){
	Graphics->render(&currTexture, spriteRender);
}

void Button::update(){
	if (!flagHover && Collision->pointIn(Input->getInput()->mx, Input->getInput()->my, dimensions)){
		flagHover = true;
		currTexture.first = textureHover;
	}
	if (flagHover && !(Collision->pointIn(Input->getInput()->mx, Input->getInput()->my, dimensions))){
		flagHover = false;
		currTexture.first = textureDefault;
	}
	if (flagHover && flagClick && Input->getInput()->m1){
		flagClick = false;
		currTexture.first = textureClick;
	}
	if (!flagClick && !(Input->getInput()->m1)){
		flagClick = true;
		currTexture.first = textureDefault;
		UIMessage msg;
		msg.type = buttonClick;
		msg.id = this->id;
		UI->pushMessage(msg);
	}
}