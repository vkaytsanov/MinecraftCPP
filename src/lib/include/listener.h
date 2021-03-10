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
	/* looping method for the m_pGame */
	virtual void render() = 0;
	/* when user has minimized or the m_pGame m_window is in the m_background */
	virtual void pause() = 0;
	/* when user has restored the m_window or the m_pGame m_window is no longer in the m_background */
	virtual void resume() = 0;
	/* when user has resized the m_window, only when maximizing, stretching or shrinking */
	virtual void resize(const int width, const int height) = 0;
};

#endif