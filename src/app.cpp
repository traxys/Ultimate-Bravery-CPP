#include "app.hpp"
#include "frame.hpp"

IMPLEMENT_APP(App);

bool App::OnInit(){
	Frame* frame = new Frame(0L, "Ultimate Bravery");
	frame->Show();
	return true;
}
