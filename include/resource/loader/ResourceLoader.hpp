/*
 * =====================================================================================
 *
 *       Filename:  ResourceLoader.hpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:31:24
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef RESOURCELOADER_HPP_
#define RESOURCELOADER_HPP_

#include <string>

#include "ResourceHandler.hpp"

class ResourceLoader {
	public:
		virtual ~ResourceLoader() = default;

		virtual void load(const char *xmlFilename, ResourceHandler &handler) = 0;
};

#endif // RESOURCELOADER_HPP_
