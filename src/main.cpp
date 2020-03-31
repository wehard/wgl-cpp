/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 16:35:01 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/31 17:12:17 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wgl.h"
#include "player.h"
#include "ball.h"
#include "opponent.h"
#include "wall.h"
#include "shader.h"
#include "obj_loader.h"
#include "mesh.h"

int main(void)
{
	wgl engine = wgl("cpp pong");
	shader basic = shader("shaders/basic.vert", "shaders/basic.frag");
	mesh l;
	load_obj("resources/logo.obj", &l);
	mesh cube;
	load_obj("resources/cube.obj", &cube);

	mesh quad;
	load_obj("resources/quad.obj", &quad);


	entity logo = entity(&basic, &l);
	logo.position = glm::vec3(0.0, 0.0, -50.0);
	logo.scale = glm::vec3(10.0f, 10.0f, 10.0f);
	logo.s = &basic;

	player p = player(&basic, &cube);
	p.position = glm::vec3(-60, 0.0, 0.0);
	p.scale = glm::vec3(1.0f, 10.0f, 1.0f);

	ball b = ball(&basic, &cube);
	b.position = glm::vec3(-50.0, 0.0, 0.0);

	opponent o = opponent(&basic, &cube, &b);
	o.position = glm::vec3(60, 0.0, 0.0);
	o.scale = glm::vec3(1.0f, 10.0f, 1.0f);

	wall left = wall(&basic, &cube);
	left.position = glm::vec3(-64.0, 0.0, 0.0);
	left.scale = glm::vec3(1.0f, 72.0f, 10.0f);

	wall right = wall(&basic, &cube);
	right.position = glm::vec3(64.0, 0.0, 0.0);
	right.scale = glm::vec3(1.0f, 72.0f, 10.0f);

	wall top = wall(&basic, &cube);
	top.position = glm::vec3(0.0, 36.0, 0.0);
	top.scale = glm::vec3(128.0f, 1.0f, 10.0f);

	wall bottom = wall(&basic, &cube);
	bottom.position = glm::vec3(0.0, -36.0, 0.0);
	bottom.scale = glm::vec3(128.0f, 1.0f, 10.0f);

	wall center = wall(&basic, &cube);
	center.position = glm::vec3(0.0, 0.0, 0.0);
	center.scale = glm::vec3(1.0f, 72.0f, 10.0f);

	engine.add_entity(&logo);
	engine.add_entity(&left);
	engine.add_entity(&right);
	engine.add_entity(&top);
	engine.add_entity(&bottom);
	engine.add_entity(&center);
	engine.add_entity(&o);
	engine.add_entity(&b);
	engine.add_entity(&p);

	engine.run();
	return (0);
}
