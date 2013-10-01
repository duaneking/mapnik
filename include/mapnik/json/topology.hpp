/*****************************************************************************
 *
 * This file is part of Mapnik (c++ mapping toolkit)
 *
 * Copyright (C) 2013 Artem Pavlenko
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *****************************************************************************/

#ifndef MAPNIK_TOPOLOGY_HPP
#define MAPNIK_TOPOLOGY_HPP

#include <vector>
#include <list>
#include <boost/variant.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/spirit/include/support_utree.hpp>
#include <boost/optional.hpp>

namespace mapnik { namespace topojson {

typedef int index_type;

struct coordinate
{
    double x;
    double y;
};

typedef boost::spirit::utree properties;

struct point
{
    coordinate coord;
    boost::optional<properties> props;
};

struct multi_point
{
    std::vector<coordinate> points;
    boost::optional<properties> props;
};

struct linestring
{
    index_type ring ;
    boost::optional<properties> props;
};

struct multi_linestring
{
    std::vector<index_type> rings;
    boost::optional<properties> props;
};

struct polygon
{
    std::vector<std::vector<index_type> > rings;
    boost::optional<properties> props;
};

struct multi_polygon
{
    std::vector<polygon> polygons;//FIXME
    boost::optional<properties> props;
};

struct invalid {};

typedef boost::variant<invalid,
                       point,
                       linestring,
                       polygon,
                       multi_point,
                       multi_linestring,
                       multi_polygon> geometry;

typedef std::tuple<double,double> pair_type;

struct arc
{
    std::list<coordinate> coordinates;
};

struct transform
{
    double scale_x = 1.0;
    double scale_y = 1.0;
    double translate_x = 0.0;
    double translate_y = 0.0;
};

struct bounding_box
{
    double minx;
    double miny;
    double maxx;
    double maxy;
};

struct topology
{
    std::vector<geometry> geometries;
    std::vector<arc> arcs;
    transform tr;
    boost::optional<bounding_box> bbox;
};

}}

BOOST_FUSION_ADAPT_STRUCT(
    mapnik::topojson::coordinate,
    (double, x)
    (double, y)
    )

BOOST_FUSION_ADAPT_STRUCT(
    mapnik::topojson::arc,
    (std::list<mapnik::topojson::coordinate>, coordinates)
    )

BOOST_FUSION_ADAPT_STRUCT(
    mapnik::topojson::transform,
    (double, scale_x)
    (double, scale_y)
    (double, translate_x)
    (double, translate_y)
    )

BOOST_FUSION_ADAPT_STRUCT(
    mapnik::topojson::bounding_box,
    (double, minx)
    (double, miny)
    (double, maxx)
    (double, maxy)
    )

BOOST_FUSION_ADAPT_STRUCT(
    mapnik::topojson::point,
    (mapnik::topojson::coordinate, coord)
    (boost::optional<mapnik::topojson::properties>, props)
    )

BOOST_FUSION_ADAPT_STRUCT(
    mapnik::topojson::multi_point,
    (std::vector<mapnik::topojson::coordinate>, points)
    (boost::optional<mapnik::topojson::properties>, props)
    )

BOOST_FUSION_ADAPT_STRUCT(
    mapnik::topojson::linestring,
    (mapnik::topojson::index_type, ring)
    (boost::optional<mapnik::topojson::properties>, props)
    )

BOOST_FUSION_ADAPT_STRUCT(
    mapnik::topojson::multi_linestring,
    (std::vector<mapnik::topojson::index_type>, rings)
    (boost::optional<mapnik::topojson::properties>, props)
    )

BOOST_FUSION_ADAPT_STRUCT(
    mapnik::topojson::polygon,
    (std::vector<std::vector<mapnik::topojson::index_type> >, rings)
    (boost::optional<mapnik::topojson::properties>, props)
    )

BOOST_FUSION_ADAPT_STRUCT(
    mapnik::topojson::multi_polygon,
    (std::vector<mapnik::topojson::polygon>, polygons)
    (boost::optional<mapnik::topojson::properties>, props)
    )

BOOST_FUSION_ADAPT_STRUCT(
    mapnik::topojson::topology,
    (std::vector<mapnik::topojson::geometry>, geometries)
    (std::vector<mapnik::topojson::arc>, arcs)
    (mapnik::topojson::transform, tr)
    (boost::optional<mapnik::topojson::bounding_box>, bbox)
   )

#endif // MAPNIK_TOPOLOGY_HPP