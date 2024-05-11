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
#include "../Builders/CameraBuilder.hpp"
#include "../Builders/RenderBuilder.hpp"
#include "../Builders/LightBuilder.hpp"
#include "../Builders/PrimitiveBuilder.hpp"

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
            parseMaterials(root["materials"]);
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

        RayTracer::Builders::CameraBuilder builder;
        std::vector<std::string> Point3DKeys = {"position", "resolution", "rotation"};
        std::vector<std::string> doubleKeys = {"fieldOfView"};

        for (const auto &key : Point3DKeys) {
            if (!setting.exists(key) || !setting[key].isGroup() ||
                !setting[key].exists("x") || !setting[key].exists("y") ||
                !setting[key].exists("z") || !setting[key]["x"].isNumber() ||
                !setting[key]["y"].isNumber() || !setting[key]["z"].isNumber())
                throw ParserException("Camera must have a " + key + " group");
            builder.set(key, Point3D(
                parseDouble(setting[key]["x"]),
                parseDouble(setting[key]["y"]),
                parseDouble(setting[key]["z"])
            ));
        }
        for (const auto &key : doubleKeys) {
            if (!setting.exists(key) || !setting[key].isNumber())
                throw ParserException("Camera must have a " + key + " number");
            builder.set(key, parseDouble(setting[key]));
        }
        std::unique_ptr<Camera> camera = std::make_unique<Camera>(builder.build());
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
        std::string type = setting["type"];
        std::unique_ptr<Lights::ILight> light = _libLoader.getLightFactory().create(setting["type"]);
        if (!light)
            throw ParserException("Light type not found");
        RayTracer::Builders::LightBuilder builder(light.get());
        std::vector<std::string> doubleKeys = {"intensity"};
        std::vector<std::string> Vector3DKeys = {"color"};

        for (const auto &key : doubleKeys) {
            if (!setting.exists(key) || !setting[key].isNumber())
                throw ParserException("Light must have a " + key + " number");
            builder.set(key, parseDouble(setting[key]));
        }
        for (const auto &key : Vector3DKeys) {
            if (!setting.exists(key) || !setting[key].isGroup() ||
                !setting[key].exists("r") || !setting[key].exists("g") ||
                !setting[key].exists("b") || !setting[key]["r"].isNumber() ||
                !setting[key]["g"].isNumber() || !setting[key]["b"].isNumber())
                throw ParserException("Light must have a " + key + " group");
            builder.set(key, Vector3D(
                parseDouble(setting[key]["r"]),
                parseDouble(setting[key]["g"]),
                parseDouble(setting[key]["b"])
            ));
        }
        builder.set("type", type);
        if (type == "point" && setting.exists("position"))
            builder.set("position", Point3D(
                parseDouble(setting["position"]["x"]),
                parseDouble(setting["position"]["y"]),
                parseDouble(setting["position"]["z"])
            ));
        if (type == "directional" && setting.exists("direction"))
            builder.set("direction", Vector3D(
                parseDouble(setting["direction"]["x"]),
                parseDouble(setting["direction"]["y"]),
                parseDouble(setting["direction"]["z"])
            ));
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
        std::string type = setting["type"];
        std::unique_ptr<Primitives::IPrimitive> primitive = _libLoader.getPrimitiveFactory().create(setting["type"]);
        if (!primitive)
            throw ParserException("Primitive type not found");
        RayTracer::Builders::PrimitiveBuilder builder(primitive.get());
        std::vector<std::string> Point3DKeys = {"position"};

        for (const auto &key : Point3DKeys) {
            if (!setting.exists(key) || !setting[key].isGroup() ||
                !setting[key].exists("x") || !setting[key].exists("y") ||
                !setting[key].exists("z") || !setting[key]["x"].isNumber() ||
                !setting[key]["y"].isNumber() || !setting[key]["z"].isNumber())
                throw ParserException("Primitive must have a " + key + " group");
            builder.set(key, Point3D(
                    parseDouble(setting[key]["x"]),
                    parseDouble(setting[key]["y"]),
                    parseDouble(setting[key]["z"])
            ));
        }

        builder.set("type", type);
        if (type == "sphere" || type == "cylinder" || type == "cone") {
            if (!setting.exists("radius") || !setting.lookup("radius").isNumber())
                throw ParserException(type + " must have a radius");
            else
                builder.set("radius", parseDouble(setting["radius"]));
        }
        if (type == "cylinder" || type == "cone") {
            if (!setting.exists("height") || !setting.lookup("height").isNumber())
                throw ParserException(type + " must have a height");
            builder.set("height", parseDouble(setting["height"]));
        }
        if (type == "plane") {
            if (!setting.exists("axis"))
                throw ParserException(type + " must have an axis");
            builder.set("axis", setting["axis"]);
        }
        if (setting.exists("translation"))
            builder.set("translation", Point3D(
                parseDouble(setting["translation"]["x"]),
                parseDouble(setting["translation"]["y"]),
                parseDouble(setting["translation"]["z"])
            ));
        if (setting.exists("rotation"))
            builder.set("rotation", Point3D(
                parseDouble(setting["rotation"]["x"]),
                parseDouble(setting["rotation"]["y"]),
                parseDouble(setting["rotation"]["z"])
            ));
        if (setting.exists("scale"))
            builder.set("scale", Point3D(
                parseDouble(setting["scale"]["x"]),
                parseDouble(setting["scale"]["y"]),
                parseDouble(setting["scale"]["z"])
            ));
        std::shared_ptr<RayTracer::Materials::IMaterial> material = _materials[setting["material"]];
        if (!material)
            throw ParserException("Material not found");
        builder.set("material", material);
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
        RayTracer::Builders::RenderBuilder builder;
        std::vector<std::string> keys = {"filename", "type"};
        std::vector<std::string> doubleKeys = {"samples", "maxDepth"};

        for (const auto &key : keys) {
            if (!setting.exists(key) || !setting[key].isString())
                throw ParserException("Rendering must have a " + key + " string");
            builder.set(key, setting);
        }
        for (const auto &key : doubleKeys) {
            if (!setting.exists(key) || !setting[key].isNumber())
                throw ParserException("Rendering must have a " + key + " number");
            builder.set(key, parseDouble(setting[key]));
        }
        std::unique_ptr<Render::IRender> render = _libLoader.getRenderFactory().create(setting["type"]);
        if (!render)
            throw ParserException("Render type not found");
        render->setFilename(builder.getFilename());
        render->setMaxDepth(builder.getMaxDepth());
        render->setSamples(builder.getSamples());
        _render = std::move(render);
    }

    std::unique_ptr<RayTracer::Render::IRender> Parser::getRender()
    {
        return std::move(_render);
    }

    void Parser::parseMaterials(const libconfig::Setting &setting)
    {
        if (!setting.isList())
            throw ParserException("Materials must be a list");
        std::size_t len = setting.getLength();
        for (std::size_t i = 0; i < len; i++)
            parseMaterial(setting[i]);
    }

    void Parser::parseMaterial(const libconfig::Setting &setting) {
        if (!setting.isGroup())
            throw ParserException("Material must be a group");
        std::unique_ptr<Materials::IMaterial> material = _libLoader.getMaterialFactory().create(setting["type"]);
        if (!material)
            throw ParserException("Material type not found");
        if (!setting.exists("type") || !setting.lookup("type").isString())
            throw ParserException("Material must have a type string");
        if (!setting.exists("name") || !setting.lookup("name").isString())
            throw ParserException("Material must have a name string");
        if (!setting.exists("color") || !setting.lookup("color").isGroup() ||
            !setting["color"].exists("r") || !setting["color"].exists("g") ||
            !setting["color"].exists("b") || !setting["color"]["r"].isNumber() ||
            !setting["color"]["g"].isNumber() || !setting["color"]["b"].isNumber())
            throw ParserException("Material must have a color group");

        material->setName(setting["name"]);
        material->setColor(
                parseDouble(setting["color"]["r"]),
                parseDouble(setting["color"]["g"]),
                parseDouble(setting["color"]["b"])
        );
        _materials[setting["name"]] = std::move(material);
    }
}
