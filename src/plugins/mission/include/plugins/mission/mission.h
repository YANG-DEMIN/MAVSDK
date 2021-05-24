// WARNING: THIS FILE IS AUTOGENERATED! As such, it should not be edited.
// Edits need to be made to the proto files
// (see https://github.com/mavlink/MAVSDK-Proto/blob/main/protos/mission/mission.proto)

#pragma once

#include <array>
#include <cmath>
#include <functional>
#include <limits>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "plugin_base.h"

namespace mavsdk {

class System;
class MissionImpl;

/**
 * @brief Enable waypoint missions.
 */
class Mission : public PluginBase {
public:
    /**
     * @brief Constructor. Creates the plugin for a specific System.
     *
     * The plugin is typically created as shown below:
     *
     *     ```cpp
     *     auto mission = Mission(system);
     *     ```
     *
     * @param system The specific system associated with this plugin.
     */
    explicit Mission(System& system); // deprecated

    /**
     * @brief Constructor. Creates the plugin for a specific System.
     *
     * The plugin is typically created as shown below:
     *
     *     ```cpp
     *     auto mission = Mission(system);
     *     ```
     *
     * @param system The specific system associated with this plugin.
     */
    explicit Mission(std::shared_ptr<System> system); // new

    /**
     * @brief Destructor (internal use only).
     */
    ~Mission();

    /**
     * @brief Type representing a mission item.
     *
     * A MissionItem can contain a position and/or actions.
     * Mission items are building blocks to assemble a mission,
     * which can be sent to (or received from) a system.
     * They cannot be used independently.
     */
    struct MissionItem {
        /**
         * @brief Possible camera actions at a mission item.
         */
        enum class CameraAction {
            None, /**< @brief No action. */
            TakePhoto, /**< @brief Take a single photo. */
            StartPhotoInterval, /**< @brief Start capturing photos at regular intervals. */
            StopPhotoInterval, /**< @brief Stop capturing photos at regular intervals. */
            StartVideo, /**< @brief Start capturing video. */
            StopVideo, /**< @brief Stop capturing video. */
        };

        /**
         * @brief Stream operator to print information about a `Mission::CameraAction`.
         *
         * @return A reference to the stream.
         */
        friend std::ostream&
        operator<<(std::ostream& str, Mission::MissionItem::CameraAction const& camera_action);

        double latitude_deg{double(NAN)}; /**< @brief Latitude in degrees (range: -90 to +90) */
        double longitude_deg{double(NAN)}; /**< @brief Longitude in degrees (range: -180 to +180) */
        float relative_altitude_m{
            float(NAN)}; /**< @brief Altitude relative to takeoff altitude in metres */
        float speed_m_s{
            float(NAN)}; /**< @brief Speed to use after this mission item (in metres/second) */
        bool is_fly_through{
            false}; /**< @brief True will make the drone fly through without stopping, while false
                       will make the drone stop on the waypoint */
        float gimbal_pitch_deg{float(NAN)}; /**< @brief Gimbal pitch (in degrees) */
        float gimbal_yaw_deg{float(NAN)}; /**< @brief Gimbal yaw (in degrees) */
        CameraAction camera_action{}; /**< @brief Camera action to trigger at this mission item */
        float loiter_time_s{float(NAN)}; /**< @brief Loiter time (in seconds) */
        double camera_photo_interval_s{
            1.0}; /**< @brief Camera photo interval to use after this mission item (in seconds) */
        float acceptance_radius_m{float(NAN)}; /**< @brief Radius for completing a mission item (in metres) */
    };

    /**
     * @brief Equal operator to compare two `Mission::MissionItem` objects.
     *
     * @return `true` if items are equal.
     */
    friend bool operator==(const Mission::MissionItem& lhs, const Mission::MissionItem& rhs);

    /**
     * @brief Stream operator to print information about a `Mission::MissionItem`.
     *
     * @return A reference to the stream.
     */
    friend std::ostream& operator<<(std::ostream& str, Mission::MissionItem const& mission_item);

    /**
     * @brief Mission plan type
     */
    struct MissionPlan {
        std::vector<MissionItem> mission_items{}; /**< @brief The mission items */
    };

    /**
     * @brief Equal operator to compare two `Mission::MissionPlan` objects.
     *
     * @return `true` if items are equal.
     */
    friend bool operator==(const Mission::MissionPlan& lhs, const Mission::MissionPlan& rhs);

    /**
     * @brief Stream operator to print information about a `Mission::MissionPlan`.
     *
     * @return A reference to the stream.
     */
    friend std::ostream& operator<<(std::ostream& str, Mission::MissionPlan const& mission_plan);

    /**
     * @brief Mission progress type.
     */
    struct MissionProgress {
        int32_t current{}; /**< @brief Current mission item index (0-based), if equal to total, the
                              mission is finished */
        int32_t total{}; /**< @brief Total number of mission items */
    };

    /**
     * @brief Equal operator to compare two `Mission::MissionProgress` objects.
     *
     * @return `true` if items are equal.
     */
    friend bool
    operator==(const Mission::MissionProgress& lhs, const Mission::MissionProgress& rhs);

    /**
     * @brief Stream operator to print information about a `Mission::MissionProgress`.
     *
     * @return A reference to the stream.
     */
    friend std::ostream&
    operator<<(std::ostream& str, Mission::MissionProgress const& mission_progress);

    /**
     * @brief Possible results returned for action requests.
     */
    enum class Result {
        Unknown, /**< @brief Unknown result. */
        Success, /**< @brief Request succeeded. */
        Error, /**< @brief Error. */
        TooManyMissionItems, /**< @brief Too many mission items in the mission. */
        Busy, /**< @brief Vehicle is busy. */
        Timeout, /**< @brief Request timed out. */
        InvalidArgument, /**< @brief Invalid argument. */
        Unsupported, /**< @brief Mission downloaded from the system is not supported. */
        NoMissionAvailable, /**< @brief No mission available on the system. */
        UnsupportedMissionCmd, /**< @brief Unsupported mission command. */
        TransferCancelled, /**< @brief Mission transfer (upload or download) has been cancelled. */
        NoSystem, /**< @brief No system connected. */
    };

    /**
     * @brief Stream operator to print information about a `Mission::Result`.
     *
     * @return A reference to the stream.
     */
    friend std::ostream& operator<<(std::ostream& str, Mission::Result const& result);

    /**
     * @brief Callback type for asynchronous Mission calls.
     */
    using ResultCallback = std::function<void(Result)>;

    /**
     * @brief Upload a list of mission items to the system.
     *
     * The mission items are uploaded to a drone. Once uploaded the mission can be started and
     * executed even if the connection is lost.
     *
     * This function is non-blocking. See 'upload_mission' for the blocking counterpart.
     */
    void upload_mission_async(MissionPlan mission_plan, const ResultCallback callback);

    /**
     * @brief Upload a list of mission items to the system.
     *
     * The mission items are uploaded to a drone. Once uploaded the mission can be started and
     * executed even if the connection is lost.
     *
     * This function is blocking. See 'upload_mission_async' for the non-blocking counterpart.
     *
     * @return Result of request.
     */
    Result upload_mission(MissionPlan mission_plan) const;

    /**
     * @brief Cancel an ongoing mission upload.
     *
     * This function is blocking.
     *
     * @return Result of request.
     */
    Result cancel_mission_upload() const;

    /**
     * @brief Callback type for download_mission_async.
     */
    using DownloadMissionCallback = std::function<void(Result, MissionPlan)>;

    /**
     * @brief Download a list of mission items from the system (asynchronous).
     *
     * Will fail if any of the downloaded mission items are not supported
     * by the MAVSDK API.
     *
     * This function is non-blocking. See 'download_mission' for the blocking counterpart.
     */
    void download_mission_async(const DownloadMissionCallback callback);

    /**
     * @brief Download a list of mission items from the system (asynchronous).
     *
     * Will fail if any of the downloaded mission items are not supported
     * by the MAVSDK API.
     *
     * This function is blocking. See 'download_mission_async' for the non-blocking counterpart.
     *
     * @return Result of request.
     */
    std::pair<Result, Mission::MissionPlan> download_mission() const;

    /**
     * @brief Cancel an ongoing mission download.
     *
     * This function is blocking.
     *
     * @return Result of request.
     */
    Result cancel_mission_download() const;

    /**
     * @brief Start the mission.
     *
     * A mission must be uploaded to the vehicle before this can be called.
     *
     * This function is non-blocking. See 'start_mission' for the blocking counterpart.
     */
    void start_mission_async(const ResultCallback callback);

    /**
     * @brief Start the mission.
     *
     * A mission must be uploaded to the vehicle before this can be called.
     *
     * This function is blocking. See 'start_mission_async' for the non-blocking counterpart.
     *
     * @return Result of request.
     */
    Result start_mission() const;

    /**
     * @brief Pause the mission.
     *
     * Pausing the mission puts the vehicle into
     * [HOLD mode](https://docs.px4.io/en/flight_modes/hold.html).
     * A multicopter should just hover at the spot while a fixedwing vehicle should loiter
     * around the location where it paused.
     *
     * This function is non-blocking. See 'pause_mission' for the blocking counterpart.
     */
    void pause_mission_async(const ResultCallback callback);

    /**
     * @brief Pause the mission.
     *
     * Pausing the mission puts the vehicle into
     * [HOLD mode](https://docs.px4.io/en/flight_modes/hold.html).
     * A multicopter should just hover at the spot while a fixedwing vehicle should loiter
     * around the location where it paused.
     *
     * This function is blocking. See 'pause_mission_async' for the non-blocking counterpart.
     *
     * @return Result of request.
     */
    Result pause_mission() const;

    /**
     * @brief Clear the mission saved on the vehicle.
     *
     * This function is non-blocking. See 'clear_mission' for the blocking counterpart.
     */
    void clear_mission_async(const ResultCallback callback);

    /**
     * @brief Clear the mission saved on the vehicle.
     *
     * This function is blocking. See 'clear_mission_async' for the non-blocking counterpart.
     *
     * @return Result of request.
     */
    Result clear_mission() const;

    /**
     * @brief Sets the mission item index to go to.
     *
     * By setting the current index to 0, the mission is restarted from the beginning. If it is set
     * to a specific index of a mission item, the mission will be set to this item.
     *
     * Note that this is not necessarily true for general missions using MAVLink if loop counters
     * are used.
     *
     * This function is non-blocking. See 'set_current_mission_item' for the blocking counterpart.
     */
    void set_current_mission_item_async(int32_t index, const ResultCallback callback);

    /**
     * @brief Sets the mission item index to go to.
     *
     * By setting the current index to 0, the mission is restarted from the beginning. If it is set
     * to a specific index of a mission item, the mission will be set to this item.
     *
     * Note that this is not necessarily true for general missions using MAVLink if loop counters
     * are used.
     *
     * This function is blocking. See 'set_current_mission_item_async' for the non-blocking
     * counterpart.
     *
     * @return Result of request.
     */
    Result set_current_mission_item(int32_t index) const;

    /**
     * @brief Check if the mission has been finished.
     *
     * This function is blocking.
     *
     * @return Result of request.
     */
    std::pair<Result, bool> is_mission_finished() const;

    /**
     * @brief Callback type for subscribe_mission_progress.
     */

    using MissionProgressCallback = std::function<void(MissionProgress)>;

    /**
     * @brief Subscribe to mission progress updates.
     */
    void subscribe_mission_progress(MissionProgressCallback callback);

    /**
     * @brief Poll for 'MissionProgress' (blocking).
     *
     * @return One MissionProgress update.
     */
    MissionProgress mission_progress() const;

    /**
     * @brief Get whether to trigger Return-to-Launch (RTL) after mission is complete.
     *
     * Before getting this option, it needs to be set, or a mission
     * needs to be downloaded.
     *
     * This function is blocking.
     *
     * @return Result of request.
     */
    std::pair<Result, bool> get_return_to_launch_after_mission() const;

    /**
     * @brief Set whether to trigger Return-to-Launch (RTL) after the mission is complete.
     *
     * This will only take effect for the next mission upload, meaning that
     * the mission may have to be uploaded again.
     *
     * This function is blocking.
     *
     * @return Result of request.
     */
    Result set_return_to_launch_after_mission(bool enable) const;

    /**
     * @brief Copy constructor.
     */
    Mission(const Mission& other);

    /**
     * @brief Equality operator (object is not copyable).
     */
    const Mission& operator=(const Mission&) = delete;

private:
    /** @private Underlying implementation, set at instantiation */
    std::unique_ptr<MissionImpl> _impl;
};

} // namespace mavsdk