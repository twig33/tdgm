#include <ui.h>
#include <managers.h>

bool flagHover = false;
bool flagClick = false;
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
	return messageQueue.pop_front();
}

void UIManager::pushMessage(UIMessage msg){
	messageQueue.push_back(msg);
}

void UIManager::createElement(UIElement element){
	UIElements.push_back(element);
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

Button::Button(int x, int y, int w, int h, std::string text){
	dimensions.x = x;
	dimensions.y = y;
	dimensions.w = w;
	dimensions.h = h;
	this->text = text;
}

void Button::update(){
	if (!flagHover && Collision->pointIn(Input->getInput()->mx, Input->getInput()->my, dimensions)){
		flagHover = true;
		currTexture->first = hoverTexture;
	}
	if (flagHover && !(Collision->pointIn(Input->getInput()->mx, Input->getInput()->my, dimensions))){
		flagHover = false;
		currTexture->first = defaultTexture;
	}
	if (flagHover && flagClick && Input->getInput()->m1){
		flagClick = false;
		currTexture->first = clickTexture;
	}
	if (!flagClick && !(Input->getInput()->m1)){
		flagClick = true;
		currTexture->first = defaultTexture;
		UIMessage msg;
		msg.type = buttonClick;
		msg.id = this->id;
		UI->pushMessage(msg);
	}
}