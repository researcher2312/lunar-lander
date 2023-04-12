#include "ui.h"

UI::UI()
{
    auto title = new GraphicalText();
    title->set_text("Lunar Lander",TITLE_FONT);
    title->set_color(color::white);
    ui_elements.push_back(title);
}

UI::~UI()
{
    for (auto ui_element: ui_elements) {
        delete(ui_element);
    }
}

void UI::draw(Renderer& renderer)
{
    for (auto ui_element: ui_elements) {
        ui_element->invoke_renderer(renderer, m_position);
    }
}
