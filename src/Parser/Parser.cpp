/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Parser
*/

#include "Parser.hpp"
#include "ALight.hpp"
#include "APrimitive.hpp"
#include <iostream>
#include "Exceptions.hpp"
#include "LibLoader.hpp"

namespace RayTracer {
    Parser::Parser(
        const char *filename,
        LibLoader &libLoader
    ) : _filename(filename),
        _libLoader(libLoader),
        _scene(nullptr)
    {
    }

    void Parser::parse()
    {
        try {
            cfg.readFile(_filename);
        } catch (const libconfig::FileIOException &fioex) {
            throw ParserException("I/O error while reading file.");
        } catch (const libconfig::ParseException &pex) {
            throw ParserException("Parse error at line " + std::to_string(pex.getLine()));
        }
        try {
            _scene = std::make_unique<Scene>();
            const libconfig::Setting &root = cfg.getRoot();
            parseCamera(root["camera"]);
            parseRender(root["render"]);
            parseLights(root["lights"]);
            parsePrimitives(root["primitives"]);
        } catch (const libconfig::SettingNotFoundException &e) {
            throw ParserException("Setting not found");
        } catch (const libconfig::SettingTypeException &e) {
            throw ParserException("Setting type error");
        } catch (const std::exception &e) {
            throw ParserException(e.what());
        }
    }

    double Parser::parseDouble(const libconfig::Setting &setting)
    {
        if (!setting.isNumber())
            throw ParserException("Setting must be a number");
        int value = setting;
        return static_cast<double>(value);
    }

    void Parser::parseCamera(const libconfig::Setting &setting)
    {
        if (!setting.isGroup())
            throw ParserException("Camera must be a group");
        if (!setting.exists("position") || !setting.lookup("position").isGroup() ||
            !setting["position"].exists("x") || !setting["position"].exists("y") ||
            !setting["position"].exists("z") || !setting["position"]["x"].isNumber() ||
            !setting["position"]["y"].isNumber() || !setting["position"]["z"].isNumber())
            throw ParserException("Camera must have a position group");
        if (!setting.exists("fieldOfView") || !setting.lookup("fieldOfView").isNumber())
            throw ParserException("Camera must have a fieldOfView number");
        if (!setting.exists("resolution") || !setting.lookup("resolution").isGroup() ||
            !setting["resolution"].exists("x") || !setting["resolution"].exists("y") ||
            !setting["resolution"]["x"].isNumber() || !setting["resolution"]["y"].isNumber())
            throw ParserException("Camera must have a resolution group");
        if (!setting.exists("rotation") || !setting.lookup("rotation").isGroup() ||
            !setting["rotation"].exists("x") || !setting["rotation"].exists("y") ||
            !setting["rotation"].exists("z") || !setting["rotation"]["x"].isNumber() ||
            !setting["rotation"]["y"].isNumber() || !setting["rotation"]["z"].isNumber())
            throw ParserException("Camera must have a rotation group");

        std::unique_ptr<Camera> camera = std::make_unique<Camera>(
            Point3D(
                    parseDouble(setting["position"]["x"]),
                    parseDouble(setting["position"]["y"]),
                    parseDouble(setting["position"]["z"])
            ),
            Point3D(
                parseDouble(setting["resolution"]["x"]),
                parseDouble(setting["resolution"]["y"]),
                0
            )
        );
        camera->setFov(parseDouble(setting["fieldOfView"]));
        camera->setRotation(
            parseDouble(setting["rotation"]["x"]),
            parseDouble(setting["rotation"]["y"]),
            parseDouble(setting["rotation"]["z"])
        );
        _scene->setCamera(camera);
    }

    void Parser::parseLights(const libconfig::Setting &setting)
    {
        if (!setting.isList())
            throw ParserException("Lights must be a list");

        std::size_t len = setting.getLength();
        for (std::size_t i = 0; i < len; i++)
            parseLight(setting[i]);
    }

    void Parser::parseLight(const libconfig::Setting &setting)
    {
        if (!setting.isGroup())
            throw ParserException("Light must be a group");
        std::unique_ptr<Lights::ILight> light = _libLoader.getLightFactory().create(setting["type"]);
        if (!light)
            throw ParserException("Light type not found");
        if (!setting.isGroup())
            throw ParserException("Light must be a group");
        if (!setting.exists("type") || !setting.lookup("type").isString())
            throw ParserException("Light must have a type string");
        if (!setting.exists("position") || !setting.lookup("position").isGroup() ||
            !setting["position"].exists("x") || !setting["position"].exists("y") ||
            !setting["position"].exists("z") || !setting["position"]["x"].isNumber() ||
            !setting["position"]["y"].isNumber() || !setting["position"]["z"].isNumber())
            throw ParserException("Light must have a position group");
        if (!setting.exists("color") || !setting.lookup("color").isGroup() ||
            !setting["color"].exists("r") || !setting["color"].exists("g") ||
            !setting["color"].exists("b") || !setting["color"]["r"].isNumber() ||
            !setting["color"]["g"].isNumber() || !setting["color"]["b"].isNumber())
            throw ParserException("Light must have a color group");
        if (!setting.exists("intensity") || !setting.lookup("intensity").isNumber())
            throw ParserException("Light must have an intensity number");
        light->setType(setting["type"]);
        light->setOrigin(
            parseDouble(setting["position"]["x"]),
            parseDouble(setting["position"]["y"]),
            parseDouble(setting["position"]["z"])
        );
        light->setColor(
            parseDouble(setting["color"]["r"]),
            parseDouble(setting["color"]["g"]),
            parseDouble(setting["color"]["b"])
        );
        light->setIntensity(parseDouble(setting["intensity"]));
        _scene->addLight(light);
    }

    void Parser::parsePrimitives(const libconfig::Setting &setting)
    {
        if (!setting.isList())
            throw ParserException("Primitives must be a list");
        std::size_t len = setting.getLength();
        for (std::size_t i = 0; i < len; i++)
            parsePrimitive(setting[i]);
    }

    void Parser::parsePrimitive(const libconfig::Setting &setting)
    {
        if (!setting.isGroup())
            throw ParserException("Primitive must be a group");
        std::unique_ptr<Primitives::IPrimitive> primitive = _libLoader.getPrimitiveFactory().create(setting["type"]);
        if (!primitive)
            throw ParserException("Primitive type not found");
        if (!setting.exists("position") || !setting.lookup("position").isGroup() ||
            !setting["position"].exists("x") || !setting["position"].exists("y") ||
            !setting["position"].exists("z") || !setting["position"]["x"].isNumber() ||
            !setting["position"]["y"].isNumber() || !setting["position"]["z"].isNumber())
            throw ParserException("Primitive must have a position group");
        if (!setting.exists("color") || !setting.lookup("color").isGroup() ||
            !setting["color"].exists("r") || !setting["color"].exists("g") ||
            !setting["color"].exists("b") || !setting["color"]["r"].isNumber() ||
            !setting["color"]["g"].isNumber() || !setting["color"]["b"].isNumber())
            throw ParserException("Primitive must have a color group");
        if (!setting.exists("reflection") || !setting.lookup("reflection").isNumber())
            throw ParserException("Primitive must have reflection");
        if (!setting.exists("transparency") || !setting.lookup("transparency").isNumber())
            throw ParserException("Primitive must have transparency");
        if (!setting.exists("type") || !setting.lookup("type").isString())
            throw ParserException("Primitive must have type");

        primitive->setType(setting["type"]);
        primitive->setOrigin(
            parseDouble(setting["position"]["x"]),
            parseDouble(setting["position"]["y"]),
            parseDouble(setting["position"]["z"])
        );
        primitive->setColor(
            parseDouble(setting["color"]["r"]),
            parseDouble(setting["color"]["g"]),
            parseDouble(setting["color"]["b"])
        );
        primitive->setTransparency(parseDouble(setting["transparency"]));
        primitive->setReflection(parseDouble(setting["reflection"]));
        if (setting.exists("radius"))
            primitive->setRadius(parseDouble(setting["radius"]));
        if (setting.exists("axis")) {
            if (setting["axis"] == "Z")
                primitive->setAxis(RayTracer::Primitives::Axis::Z);
            else if (setting["axis"] == "Y")
                primitive->setAxis(RayTracer::Primitives::Axis::Y);
            else if (setting["axis"] == "X")
                primitive->setAxis(RayTracer::Primitives::Axis::X);
            else
                throw ParserException("Unknown axis");
        }
        _scene->addPrimitive(primitive);
    }

    std::unique_ptr<Scene> &Parser::getScene()
    {
        return _scene;
    }

    void Parser::parseRender(const libconfig::Setting &setting)
    {
        if (!setting.isGroup())
            throw ParserException("Rendering must be a group");
        std::unique_ptr<Render::IRender> render = _libLoader.getRenderFactory().create(setting["type"]);
        if (!render)
            throw ParserException("Render type not found");
        if (!setting.exists("filename") || !setting.lookup("filename").isString())
            throw ParserException("Render must have a filename string");
        render->setFilename(setting["filename"]);
        _render = std::move(render);
    }

    std::unique_ptr<RayTracer::Render::IRender> Parser::getRender()
    {
        return std::move(_render);
    }
}
