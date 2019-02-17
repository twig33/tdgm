#include <graphics.h>
#include <queue>
enum UIMessageTypes{buttonClick};
class UIElement{
	virtual void renderMe();
	virtual void update();
	int type;
};

class Button : UIElement{
	public:
		int id;
		SDL_Texture* textureDefault;
		SDL_Texture* textureHover;
		SDL_Texture* textureClick;
		Texture currTexture;
		SDL_Rect dimensions;
		std::string text;
		virtual void renderMe;
		virtual void update();
		Button(int x, int y, int w, int h);
};

class UIMessage{
	int type;
	int id;
};

class UIManager{
	public:
		void updateUI();
		UIMessage dispatchMessage();
		void pushMessage(UIMessage msg);
		void handleMessage(UIMessage msg);
		void createElement(UIElement element);
		UIManager();
	private:
		std::queue<UIMessage> messageQueue;
		std::vector<UIElement> UIElements;
};
