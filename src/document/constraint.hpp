#pragma once
#include "util/uuid.hpp"
#include "nlohmann/json_fwd.hpp"
#include "item_kind.hpp"
#include "constraint_visitor.hpp"
#include <memory>
#include <set>

namespace dune3d {
using json = nlohmann::json;

class Document;

class Constraint {
public:
    UUID m_uuid;
    enum class Type {
        POINTS_COINCIDENT,
        PARALLEL,
        POINT_ON_LINE,
        POINT_ON_CIRCLE,
        EQUAL_LENGTH,
        EQUAL_RADIUS,
        SAME_ORIENTATION,
        HORIZONTAL,
        VERTICAL,
        POINT_DISTANCE,
        POINT_DISTANCE_HORIZONTAL,
        POINT_DISTANCE_VERTICAL,
        WORKPLANE_NORMAL,
        MIDPOINT,
        DIAMETER,
        RADIUS,
        ARC_LINE_TANGENT,
        ARC_ARC_TANGENT,
        LINE_POINTS_PERPENDICULAR,
    };
    virtual Type get_type() const = 0;
    std::string get_type_name() const;

    virtual ~Constraint();
    virtual json serialize() const;

    static std::unique_ptr<Constraint> new_from_json(const UUID &uu, const json &j);
    virtual std::unique_ptr<Constraint> clone() const = 0;

    bool is_valid(const Document &doc) const;

    virtual void accept(ConstraintVisitor &visitor) const = 0;

    UUID m_group;

    ItemKind m_kind = ItemKind::USER;

    virtual std::set<UUID> get_referenced_entities() const = 0;

protected:
    explicit Constraint(const UUID &uu);
    explicit Constraint(const UUID &uu, const json &j);
};

} // namespace dune3d
