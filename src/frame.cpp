#include "frame.hpp"

Frame::Frame(wxFrame *frame, const wxString& title) : wxFrame(frame, -1, title, wxPoint(100,100),wxDefaultSize,wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX){
	SetSize(500,200);
}
