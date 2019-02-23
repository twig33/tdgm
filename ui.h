#ifndef UI_INCLUDED
#define UI_INCLUDED

#include <graphics.h>
#include <queue>
enum UIMessageTypes{buttonClick};
enum UIElementTypes{button};

class UIElement{
	public:
		virtual void renderMe();
		virtual void update();
		int type;
};

class Button : public UIElement{
	public:
		int id;
		SDL_Texture* textureDefault;
		SDL_Texture* textureHover;
		SDL_Texture* textureClick;
		Texture currTexture;
		SDL_Rect dimensions;
		std::string text;
		virtual void renderMe();
		virtual void update();
		Button(int x, int y, int w, int h, std::string textt, int idd);
};

class UIMessage{
	public:
		int type;
		int id;
};

class UIManager{
	public:
		void updateUI();
		UIMessage dispatchMessage();
		void pushMessage(UIMessage msg);
		void handleMessage(UIMessage msg);
		void createElement(UIElement* element);
		UIManager();
	private:
		std::queue<UIMessage> messageQueue;
		std::vector<UIElement> UIElements;
};
#endif