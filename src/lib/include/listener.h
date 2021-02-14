#ifndef LISTENER
#define LISTENER
/* Main class should extend this */
class Listener {
public:
    /* create only platform dependent things */
    Listener() = default;
    /* free the whole memory */
    virtual ~Listener() = default;
    /* create all platform independent things */
	virtual void create() = 0;
	/* looping method for the game */
	virtual void render() = 0;
	/* when user has minimized or the game window is in the background */
	virtual void pause() = 0;
	/* when user has restored the window or the game window is no longer in the background */
	virtual void resume() = 0;
	/* when user has resized the window, only when maximizing, stretching or shrinking */
	virtual void resize(const int& width, const int& height) = 0;
};

#endif