#pragma once

#include "Renderable2D.h"

class Label : public Renderable2D
{
public:
	Label(const std::string& text, float x, float y, unsigned int color);
	virtual ~Label();

	virtual void submit(Renderer2D* renderer) const override;
private:
	std::string m_Text;
};