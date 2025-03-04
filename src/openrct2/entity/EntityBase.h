#pragma once

#include "../Identifiers.h"
#include "../common.h"
#include "../world/Location.hpp"

enum class EntityType : uint8_t
{
    Vehicle,
    Guest,
    Staff,
    Litter,
    SteamParticle,
    MoneyEffect,
    CrashedVehicleParticle,
    ExplosionCloud,
    CrashSplash,
    ExplosionFlare,
    JumpingFountain,
    Balloon,
    Duck,
    Count,
    Null = 255
};

struct EntitySpriteData
{
    // Width from centre of sprite to edge
    uint8_t Width;
    // Height from centre of sprite to bottom
    uint8_t HeightMin;
    // Height from centre of sprite to top
    uint8_t HeightMax;
    // Screen Coordinates of sprite
    ScreenRect SpriteRect;
};

namespace EntityRenderFlags
{
    // Disables tweening for this tick, this is helpful when entities are teleported
    // and should not be tweened.
    constexpr uint32_t kInvalidateTweening = (1U << 0);

} // namespace EntityRenderFlags

struct EntityBase
{
    EntityType Type;
    EntityId Id;
    int32_t x;
    int32_t y;
    int32_t z;
    // Rendering specific flags, this should not be stored in the save file.
    uint32_t RenderFlags;
    EntitySpriteData SpriteData;
    // Used as direction or rotation depending on the entity.
    uint8_t Orientation;

    /**
     * Moves a sprite to a new location, invalidates the current position if valid
     * and also the new position.
     *
     *  rct2: 0x0069E9D3
     */
    void MoveTo(const CoordsXYZ& newLocation);

    /**
     * Sets the entity location without screen invalidation.
     */
    void SetLocation(const CoordsXYZ& newLocation);

    /**
     * Gets the entity current location.
     */
    CoordsXYZ GetLocation() const;

    void Invalidate();
    template<typename T> bool Is() const;
    template<typename T> T* As()
    {
        return Is<T>() ? reinterpret_cast<T*>(this) : nullptr;
    }
    template<typename T> const T* As() const
    {
        return Is<T>() ? reinterpret_cast<const T*>(this) : nullptr;
    }

    void Serialise(class DataSerialiser& stream);

    void Paint() const;
};
