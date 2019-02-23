///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "AboutDialog_B.h"

///////////////////////////////////////////////////////////////////////////

AboutDialog_B::AboutDialog_B( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("MySweeper 1.0.3-rc\nCopyright © 2014 by Thomas Senfter\ne-mail: thomassenfter@gmx.at"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText2->Wrap( 480 );
	m_staticText2->SetFont( wxFont( 12, 70, 90, 92, false, wxEmptyString ) );
	
	bSizer2->Add( m_staticText2, 0, wxALIGN_CENTER|wxALL, 20 );
	
	m_staticline2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer2->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );
	
	m_staticText21 = new wxStaticText( this, wxID_ANY, wxT("Used Libraries: wxWidgets, crypto++, pugixml\nSpecial thanks to Lorenz Weiler"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText21->Wrap( -1 );
	m_staticText21->SetFont( wxFont( 10, 70, 90, 92, false, wxEmptyString ) );
	
	bSizer2->Add( m_staticText21, 0, wxALIGN_CENTER|wxALL, 20 );
	
	m_staticline3 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer2->Add( m_staticline3, 0, wxEXPAND | wxALL, 5 );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE."), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText3->Wrap( 480 );
	bSizer2->Add( m_staticText3, 0, wxALL, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer2->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	ok_button = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( ok_button, 0, wxALIGN_CENTER|wxALL, 10 );
	
	
	this->SetSizer( bSizer2 );
	this->Layout();
	bSizer2->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	ok_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboutDialog_B::ok ), NULL, this );
}

AboutDialog_B::~AboutDialog_B()
{
	// Disconnect Events
	ok_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboutDialog_B::ok ), NULL, this );
	
}
