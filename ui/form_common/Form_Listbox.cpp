#include "Form_Listbox.hpp"
#include "Form_Groupbox.hpp"

using namespace CORE;

Form_Listbox::Form_Listbox(const std::vector<std::string>* items, size_t* selected) {

	_type = E_UI_ELEMENT_TYPE::UI_ELEMENT_CONTROL;
	_selectedVar = selected;

	_size = { 0, (UI_CONTROL::LISTBOX_ITEM_SPACING._y * UI_CONTROL::LISTBOX_ITEMS) + (5 * 2) };
	_items = items;
}

Form_Listbox::~Form_Listbox() {

}

void Form_Listbox::render() {

	const auto& pos = _absolutePosition;
	const auto& size = getSize();

	UI_RenderFactory::get().getImpl()->drawRectFill(pos._x, pos._y, size._x, size._y, UI_COLORS::CONTROL_FILL);
	UI_RenderFactory::get().getImpl()->drawRect(pos._x, pos._y, size._x, size._y, UI_COLORS::CONTROL_OUTLINE);

	// if we are not at the top
	if (_scroll > 0) {

	}

	// if we are not at the bottom
	if (_scroll + UI_CONTROL::LISTBOX_ITEMS < (_items->size() - 1)) {

	}

	// draw items 
	for (size_t i = _scroll; i < std::min<size_t>(UI_CONTROL::LISTBOX_ITEMS + _scroll, _items->size()); i++) {
		UI_RenderFactory::get().getImpl()->drawString(_textPosition._x , _textPosition._y + ((i - _scroll) * UI_CONTROL::LISTBOX_ITEM_SPACING._y), UI_FONTS::CONTROL_FONT, (i == _selected) ? UI_COLORS::LIGHT_BLUE : (i == _cursor) ? UI_COLORS::CONTROL_FILL_3 : UI_COLORS::WHITE, _items->at(i));
	}
}

void Form_Listbox::update() {

	auto parent = dynamic_pointer_cast<Form_Groupbox>(getParent());

	_absolutePosition = parent->getControlPosition() + getPosition();
	_textPosition = _absolutePosition + POINT_INT(5, 5);
}

void Form_Listbox::input() {

	const auto& pos = _absolutePosition;
	const auto& size = getSize();

	if (UI_INPUT::mouseInBounds(pos._x, pos._y, size._x, size._y)) {

		if (UI_INPUT::scrollState() > 0) {

			// move up
			if (_scroll > 0) {
				_scroll -= 1;
			}
		}
		else if (UI_INPUT::scrollState() < 0) {

			if (_scroll + UI_CONTROL::LISTBOX_ITEMS <= static_cast<int>(_items->size() - 1)) {
				_scroll += 1;
			}
		}
		else if (UI_INPUT::mouseDelta().x != 0 || UI_INPUT::mouseDelta().y != 0) {

			// check for hover
			for (size_t i = _scroll; i < std::min<size_t>(UI_CONTROL::LISTBOX_ITEMS + _scroll, _items->size()); i++) {

				auto pos = POINT_INT(_absolutePosition._x, _textPosition._y + ((i - _scroll) * UI_CONTROL::LISTBOX_ITEM_SPACING._y));
				auto size = POINT_INT(getSize()._x, UI_CONTROL::LISTBOX_ITEM_SPACING._y);

				if (UI_INPUT::mouseInBounds(pos._x, pos._y, size._x, size._y)) {

					_cursor = i;
				}
			}
		}

		if (UI_INPUT::isPressed(VK_LBUTTON)) {
			_selected = _cursor;
		}
	}
}
