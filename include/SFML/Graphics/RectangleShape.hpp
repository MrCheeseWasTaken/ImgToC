////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2018 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef SFML_RECTANGLESHAPE_HPP
#define SFML_RECTANGLESHAPE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Shape.hpp>


namespace sf
{
////////////////////////////////////////////////////////////
/// \brief Specialized shape representing a shape
///
////////////////////////////////////////////////////////////
class SFML_GRAPHICS_API RectangleShape : public Shape
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// \param size Size of the shape
    ///
    ////////////////////////////////////////////////////////////
    explicit RectangleShape(const Vector2f& size = Vector2f(0, 0));

    ////////////////////////////////////////////////////////////
    /// \brief Set the size of the shape
    ///
    /// \param size New size of the shape
    ///
    /// \see getSize
    ///
    ////////////////////////////////////////////////////////////
    void setSize(const Vector2f& size);

    ////////////////////////////////////////////////////////////
    /// \brief Get the size of the shape
    ///
    /// \return Size of the shape
    ///
    /// \see setSize
    ///
    ////////////////////////////////////////////////////////////
    const Vector2f& getSize() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the number of points defining the shape
    ///
    /// \return Number of points of the shape. For shape
    ///         shapes, this number is always 4.
    ///
    ////////////////////////////////////////////////////////////
    virtual std::size_t getPointCount() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get a point of the shape
    ///
    /// The returned point is in local coordinates, that is,
    /// the shape's transforms (position, rotation, scale) are
    /// not taken into account.
    /// The result is undefined if \a index is out of the valid range.
    ///
    /// \param index Index of the point to get, in range [0 .. 3]
    ///
    /// \return index-th point of the shape
    ///
    ////////////////////////////////////////////////////////////
    virtual Vector2f getPoint(std::size_t index) const;

private:

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    Vector2f m_size; ///< Size of the shape
};

} // namespace sf


#endif // SFML_RECTANGLESHAPE_HPP


////////////////////////////////////////////////////////////
/// \class sf::RectangleShape
/// \ingroup graphics
///
/// This class inherits all the functions of sf::Transformable
/// (position, rotation, scale, bounds, ...) as well as the
/// functions of sf::Shape (outline, color, texture, ...).
///
/// Usage example:
/// \code
/// sf::RectangleShape shape;
/// shape.setSize(sf::Vector2f(100, 50));
/// shape.setOutlineColor(sf::Color::Red);
/// shape.setOutlineThickness(5);
/// shape.setPosition(10, 20);
/// ...
/// window.draw(shape);
/// \endcode
///
/// \see sf::Shape, sf::CircleShape, sf::ConvexShape
///
////////////////////////////////////////////////////////////
