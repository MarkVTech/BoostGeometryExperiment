#pragma once

class ICommon
{
public:
    virtual ~ICommon() {}

    virtual void highlight(bool highlighted) = 0;
    bool isHighlighted() const { return mIsHighlighted; }

protected:
    bool mIsHighlighted = false;
};
