#pragma once
#include <iostream>
class Remote;
class Tv {
public:
	friend class Remote;
	enum {Off, On};
	enum {MinVal, MaxVal = 20};
	enum{Antenna, Cable};
	enum {TV, DVD};

private:
	int state;
	int volume;
	int maxchannel;
	int channel;
	int mode;
	int input;

public:
	Tv(int s = Off, int mc = 125)
		: state(s),
		volume(5),
		maxchannel(mc),
		channel(2),
		mode(Cable),
		input(DVD) {}
	void onoff() { state = (state == On) ? Off : On; }
	bool ison() const { return state == On; }
	bool volup();
	bool voldown();
	void chanup();
	void chandown();
	void set_mode() { mode = (mode == Antenna) ? Cable : Antenna; }
	void set_input() { input = (input == TV) ? DVD : TV; }
	void show_settings() const;
	void set_remote_mode(Remote& r)const;
};
class Remote {
public:
	friend class Tv;
	enum { Normal, Interactive };

private:
	int mode;
	int gmode;

public:
	Remote(int m = Tv::TV) : mode(m), gmode(Normal) {}
	bool volup(Tv& t) { return t.volup(); }
	bool voldown(Tv& t) { return t.voldown(); }
	void onoff(Tv& t) { t.onoff(); }
	void chanup(Tv& t) { t.chanup(); }
	void chandown(Tv& t) { t.chandown(); }
	void set_chan(Tv& t, int c) { t.channel = c; }
	void set_mode(Tv& t) { t.set_mode(); }
	void set_input(Tv& t) { t.set_input(); }
	void show_remote_mode() const;
	void set_remote_mode();
};
inline void Remote::show_remote_mode() const {
	std::cout << (gmode == Normal ? "Normal" : "Interactive") << std::endl;
}

inline void Remote::set_remote_mode() {
	gmode = (gmode == Normal) ? Interactive : Normal;
}
