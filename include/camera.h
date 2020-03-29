/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 09:47:00 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/29 12:32:51 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <glm/glm.hpp>

class camera
{
private:
	glm::vec3 rotation;
	float	fov;
public:
	glm::vec3 position;
	camera(/* args */);
	~camera();
	glm::mat4x4 get_view_matrix();
};
