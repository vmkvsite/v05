#include <tchar.h>
#include "nwpwin.h"
#include <list>

class main_window : public vsite::nwp::window
{
private:
	std::list<POINT> m_points;

protected:
	void on_paint(HDC hdc) override
	{
		if (m_points.empty())
			return;

		auto it = m_points.begin();
		MoveToEx(hdc, it->x, it->y, NULL);

		++it;
		for (; it != m_points.end(); ++it) {
			LineTo(hdc, it->x, it->y);
		}
	}

	void on_left_button_down(POINT p) override
	{
		m_points.push_back(p);
		::InvalidateRect(*this, NULL, TRUE);
	}

	void on_key_down(int vk) override
	{
		switch (vk) {
		case VK_ESCAPE:
			m_points.clear();
			::InvalidateRect(*this, NULL, TRUE);
			break;

		case VK_BACK:
			if (!m_points.empty()) {
				m_points.pop_back();
				::InvalidateRect(*this, NULL, TRUE);
			}
			break;
		}
	}

	void on_destroy() override
	{
		::PostQuitMessage(0);
	}
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 5");
	return app.run();
}