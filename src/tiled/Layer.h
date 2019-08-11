//
// Created by robin on 01.08.2019.
//

#ifndef TILESON_LAYER_H
#define TILESON_LAYER_H

#include "json.hpp"
#include "../objects/Vector2.hpp"
#include "../objects/Color.hpp"
#include "Chunk.h"
#include "Object.h"
#include "../objects/Property.h"
#include "../objects/PropertyCollection.h"

namespace tson
{
    class Layer
    {
        public:
            //'type': tilelayer, objectgroup, imagelayer or group
            enum class Type : uint8_t
            {
                Undefined = 0,
                TileLayer = 1,
                ObjectGroup = 2,
                ImageLayer = 3,
                Group = 4
            };

            Layer() = default;
            explicit Layer(const nlohmann::json &json);
            bool parse(const nlohmann::json &json);

            [[nodiscard]] const std::string &getCompression() const;
            [[nodiscard]] const std::vector<int> &getData() const;
            [[nodiscard]] const std::string &getBase64Data() const;
            [[nodiscard]] const std::string &getDrawOrder() const;
            [[nodiscard]] const std::string &getEncoding() const;
            [[nodiscard]] int getId() const;
            [[nodiscard]] const std::string &getImage() const;
            [[nodiscard]] const std::string &getName() const;
            [[nodiscard]] const Vector2f &getOffset() const;
            [[nodiscard]] float getOpacity() const;
            [[nodiscard]] const Vector2i &getSize() const;
            [[nodiscard]] const Colori &getTransparentcolor() const;

            Type getType() const;

            [[nodiscard]] const std::string &getTypeStr() const;
            [[nodiscard]] bool isVisible() const;
            [[nodiscard]] int getX() const;
            [[nodiscard]] int getY() const;

            [[nodiscard]] std::vector<tson::Chunk> &getChunks();
            [[nodiscard]] std::vector<tson::Layer> &getLayers();
            [[nodiscard]] std::vector<tson::Object> &getObjects();
            [[nodiscard]] PropertyCollection &getProperties();

            template <typename T>
            T get(const std::string &name);
            tson::Property * getProp(const std::string &name);

        private:
            void setTypeByString();

            std::vector<tson::Chunk>               m_chunks; 	       /*! 'chunks': Array of chunks (optional). tilelayer only. */
            std::string                            m_compression;      /*! 'compression': zlib, gzip or empty (default). tilelayer only. */
            std::vector<int>                       m_data;             /*! 'data' (when uint array): Array of unsigned int (GIDs) or base64-encoded
                                                                        *   data. tilelayer only. */
            std::string                            m_base64Data;       /*! 'data' (when string):     Array of unsigned int (GIDs) or base64-encoded
                                                                        *   data. tilelayer only. */
            std::string                            m_drawOrder;        /*! 'draworder': topdown (default) or index. objectgroup only. */
            std::string                            m_encoding;         /*! 'encoding': csv (default) or base64. tilelayer only. */
            int                                    m_id{};             /*! 'id': Incremental id - unique across all layers */
            std::string                            m_image;            /*! 'image': Image used by this layer. imagelayer only. */
            std::vector<tson::Layer>               m_layers; 	       /*! 'layers': Array of layers. group on */
            std::string                            m_name;             /*! 'name': Name assigned to this layer */
            std::vector<tson::Object>              m_objects;          /*! 'objects': Array of objects. objectgroup only. */
            tson::Vector2f                         m_offset;           /*! 'offsetx' and 'offsety': Horizontal and Vertical layer offset in pixels
                                                                        *  (default: {0, 0}) */
            float                                  m_opacity{};        /*! 'opacity': Value between 0 and 1 */
            tson::PropertyCollection               m_properties; 	   /*! 'properties': A list of properties (name, value, type). */
            tson::Vector2i                         m_size;             /*! x = 'width': (Column count. Same as map width for fixed-size maps.)
                                                                           y = 'height': Row count. Same as map height for fixed-size maps. */
            tson::Colori                           m_transparentcolor; /*! 'transparentcolor': Hex-formatted color (#RRGGBB) (optional, imagelayer only */
            std::string                            m_typeStr;          /*! 'type': tilelayer, objectgroup, imagelayer or group */
            Layer::Type                            m_type;             /*! Layer type as enum*/
            bool                                   m_visible{};        /*! 'visible': Whether layer is shown or hidden in editor */
            int                                    m_x{};              /*! 'x': Horizontal layer offset in tiles. Always 0. */
            int                                    m_y{};              /*! 'y': Vertical layer offset in tiles. Always 0. */
    };

    /*!
     * A shortcut for getting a property. Alternative to getProperties().getValue<T>("<name>")
     * @tparam T The template value
     * @param name Name of the property
     * @return The actual value, if it exists. Otherwise: The default value of the type.
     */
    template<typename T>
    T Layer::get(const std::string &name)
    {
        return m_properties.getValue<T>(name);
    }
}

#endif //TILESON_LAYER_H
