//
//  main.cpp
//
//
//  Created by Lee Maguire on 28/07/2022.
//

#include <chrono>
#include <semaphore>
#include <stdio.h>
#include <thread>
#include "event_loop.hpp"
#include <cpprealm/sdk.hpp>
#include <realm/object-store/sync/sync_session.hpp>

struct DVRDatum: realm::object {

    realm::persisted<int> _id;      // not object ID yet. Could be UUID?
    realm::persisted<std::string> accounthash;
    realm::persisted<std::string> assetname;
    realm::persisted<int> bumpflags;
    realm::persisted<int> category;
    realm::persisted<std::string> chname;
    realm::persisted<int> chnum;
    realm::persisted<std::string> circuithash;
    realm::persisted<std::string> devicehash;
    realm::persisted<std::string> dtlastupdatedate;
    realm::persisted<int> dvrid;
    realm::persisted<int> earlymins;
    realm::persisted<int> epgduration;
    realm::persisted<int> epgstarttime;
    realm::persisted<std::string> episodename;
    realm::persisted<std::string> genre;
    realm::persisted<int> imgflags;
    realm::persisted<int> lastwatched;
    realm::persisted<int> latemins;
    realm::persisted<std::string> numbertokeep;
    realm::persisted<int> parentid;
    realm::persisted<std::string> progname;
    realm::persisted<int> programid;        // not <long>, but we do have Int64hgy
    realm::persisted<std::string> progtmsid;
    realm::persisted<std::string> pvrorder;
    realm::persisted<std::string> rating;
    realm::persisted<int> rcrdduration;
    realm::persisted<int> rcrdflags;
    realm::persisted<int> rcrdquality;
    realm::persisted<int> rcrdstarttime;
    realm::persisted<int> rcrdtype;
    realm::persisted<int> resumepoint;
    realm::persisted<int> scheduledtime;
    realm::persisted<std::string> seriesflags;
    realm::persisted<int> seriesid;
    realm::persisted<std::string> seriesname;
    realm::persisted<int> seriesrootid;
    realm::persisted<std::string> seriestmsid;
    realm::persisted<int> serviceid;
    realm::persisted<std::string> srcclienthash;
    realm::persisted<std::string> state;
    realm::persisted<std::string> status;
    realm::persisted<std::string> teamaid;
    realm::persisted<int> teambid;
    realm::persisted<int> tmsserviceid;
    
    using schema = realm::schema<
    "DVRDatumCollection",
    realm::property<"_id", &DVRDatum::_id, true>,
    realm::property<"accounthash", &DVRDatum::accounthash>,
    realm::property<"assetname", &DVRDatum::assetname>,
    realm::property<"bumpflags", &DVRDatum::bumpflags>,
    realm::property<"category", &DVRDatum::category>,
    realm::property<"chname", &DVRDatum::chname>,
    realm::property<"chnum", &DVRDatum::chnum>,
    realm::property<"circuithash", &DVRDatum::circuithash>,
    realm::property<"devicehash", &DVRDatum::devicehash>,
    realm::property<"dtlastupdatedate", &DVRDatum::dtlastupdatedate>,
    realm::property<"dvrid", &DVRDatum::dvrid>,
    realm::property<"earlymins", &DVRDatum::earlymins>,
    realm::property<"epgduration", &DVRDatum::epgduration>,
    realm::property<"epgstarttime", &DVRDatum::epgstarttime>,
    realm::property<"episodename", &DVRDatum::episodename>,
    realm::property<"genre", &DVRDatum::genre>,
    realm::property<"imgflags", &DVRDatum::imgflags>,
    realm::property<"lastwatched", &DVRDatum::lastwatched>,
    realm::property<"latemins", &DVRDatum::latemins>,
    realm::property<"numbertokeep", &DVRDatum::numbertokeep>,
    realm::property<"parentid", &DVRDatum::parentid>,
    realm::property<"progname", &DVRDatum::progname>,
    realm::property<"programid", &DVRDatum::programid>,
    realm::property<"progtmsid", &DVRDatum::progtmsid>,
    realm::property<"pvrorder", &DVRDatum::pvrorder>,
    realm::property<"rating", &DVRDatum::rating>,
    realm::property<"rcrdduration", &DVRDatum::rcrdduration>,
    realm::property<"rcrdflags", &DVRDatum::rcrdflags>,
    realm::property<"rcrdquality", &DVRDatum::rcrdquality>,
    realm::property<"rcrdstarttime", &DVRDatum::rcrdstarttime>,
    realm::property<"rcrdtype", &DVRDatum::rcrdtype>,
    realm::property<"resumepoint", &DVRDatum::resumepoint>,
    realm::property<"scheduledtime", &DVRDatum::scheduledtime>,
    realm::property<"seriesflags", &DVRDatum::seriesflags>,
    realm::property<"seriesid", &DVRDatum::seriesid>,
    realm::property<"seriesname", &DVRDatum::seriesname>,
    realm::property<"seriesrootid", &DVRDatum::seriesrootid>,
    realm::property<"seriestmsid", &DVRDatum::seriestmsid>,
    realm::property<"serviceid", &DVRDatum::serviceid>,
    realm::property<"srcclienthash", &DVRDatum::srcclienthash>,
    realm::property<"state", &DVRDatum::state>,
    realm::property<"status", &DVRDatum::status>,
    realm::property<"teamaid", &DVRDatum::teamaid>,
    realm::property<"teambid", &DVRDatum::teambid>,
    realm::property<"tmsserviceid", &DVRDatum::tmsserviceid>>;
};

DVRDatum make_sample_1() {
    auto dvr_device = DVRDatum();
    dvr_device._id = 1;
    dvr_device.devicehash = "john";

    return dvr_device;
}

DVRDatum make_sample_102() {
    auto dvr_device = DVRDatum();
    dvr_device._id = 102;       // ObjectId("62b49570996b13f09c4efe4e")
    dvr_device.accounthash = "eb9c1c569d9d32354797454e42082a4ec4eef9b16fa371f7cf0acdf4db0faeeb";
    dvr_device.dvrid = 11;
    dvr_device.devicehash = "476c6bab84ccc093ab6928e619db82b28db34c376c94d6b87dd21dd64f7f0769";
    dvr_device.assetname = "a_GCvrry_JClBQ9";
    dvr_device.bumpflags = 3630;
    dvr_device.category = 144;
    dvr_device.chname = "HD PPV 2";
    dvr_device.chnum = 1002;
    dvr_device.circuithash = "";
    dvr_device.dtlastupdatedate = "2022-03-29 19:49:51.997+0000";
    dvr_device.earlymins = 0;
    dvr_device.epgduration = 3600;
    dvr_device.epgstarttime = 1332529200;
    dvr_device.episodename = "";
    dvr_device.genre = "Sports & Fitness";
    dvr_device.imgflags = 1332529170;
    dvr_device.lastwatched = 1332529823;
    dvr_device.latemins = 0;
    dvr_device.numbertokeep = "";
    dvr_device.parentid = 0;
    dvr_device.progname = "Women's Extreme Wrestling: Girl Squad";
    dvr_device.programid = 4109257595;  //should be long
    dvr_device.progtmsid = "SH041754700000";
    dvr_device.pvrorder = "";
    dvr_device.rating = "TV-14";
    dvr_device.rcrdduration = 3661;
    dvr_device.rcrdflags = 432;
    dvr_device.rcrdquality = 1;
    dvr_device.rcrdstarttime = 1332529170;
    dvr_device.rcrdtype = 0;
    dvr_device.resumepoint = 211;
    dvr_device.scheduledtime = 1332528657;
    dvr_device.seriesflags = "";
    dvr_device.seriesid = 0;
    dvr_device.seriesname = "";
    dvr_device.seriesrootid = 21457377;
    dvr_device.seriestmsid = "";
    dvr_device.serviceid = 13552;
    dvr_device.srcclienthash = "c1306b7b64eebc60972217ce8601c6c27718df9e2f540e3544959c8215551a03";
    dvr_device.state = "recorded";
    dvr_device.status = "stopRecording";
    dvr_device.teamaid = "";
    dvr_device.teambid = 0;
    dvr_device.tmsserviceid = 120420;
    
    return dvr_device;
}

DVRDatum make_sample_103() {
    auto dvr_device = DVRDatum();
    dvr_device._id = 103;       // ObjectId("62b49570996b13f09c4efe50")
    dvr_device.accounthash = "eb9c1c569d9d32354797454e42082a4ec4eef9b16fa371f7cf0acdf4db0faeeb";
    dvr_device.dvrid = 16;
    dvr_device.devicehash = "ab09f9063a8ddec800c37a465a19464d530cc2ed7fd53f36ab71ee846339ca6d";
    dvr_device.assetname = "a_lqyrmT_7VHy8v";
    dvr_device.bumpflags = 0;
    dvr_device.category = 93;
    dvr_device.chname = "CBS WCBS";
    dvr_device.chnum = 502;
    dvr_device.circuithash = "";
    dvr_device.dtlastupdatedate = "2022-01-18 16:26:38.244+0000";
    dvr_device.earlymins = 0;
    dvr_device.epgduration = 3600;
    dvr_device.epgstarttime = 1326074400;
    dvr_device.episodename = "Who Has This One in the Bag?";
    dvr_device.genre = "";
    dvr_device.imgflags = 0;
    dvr_device.lastwatched = 0;
    dvr_device.latemins = 0;
    dvr_device.numbertokeep = "";
    dvr_device.parentid = 13;
    dvr_device.progname = "The Amazing Race";
    dvr_device.programid = 2158528683;  //should be long
    dvr_device.progtmsid = "EP004468530472";
    dvr_device.pvrorder = "";
    dvr_device.rating = "";
    dvr_device.rcrdduration = 2379;
    dvr_device.rcrdflags = 3504;
    dvr_device.rcrdquality = 1;
    dvr_device.rcrdstarttime = 1326074371;
    dvr_device.rcrdtype = 1;
    dvr_device.resumepoint = 0;
    dvr_device.scheduledtime = 1326066563;
    dvr_device.seriesflags = "";
    dvr_device.seriesid = 1979913767;
    dvr_device.seriesname = "";
    dvr_device.seriesrootid = 188109;
    dvr_device.seriestmsid = "SH004468530000";
    dvr_device.serviceid = 751;
    dvr_device.srcclienthash = "";
    dvr_device.state = "recorded";
    dvr_device.status = "stopRecording";
    dvr_device.teamaid = "";
    dvr_device.teambid = 0;
    dvr_device.tmsserviceid = 16689;
    
    return dvr_device;
}

realm::task<void> wait_for_sync_uploads(const realm::User& user) {
    auto sync_sessions = user.m_user->sync_manager()->get_all_sessions();
    auto session = sync_sessions[0];
    co_await realm::make_awaitable<std::error_code>([&] (auto cb) {
        session->wait_for_upload_completion(cb);
    });
    co_return;
}

realm::task<void> wait_for_sync_downloads(const realm::User& user) {
    auto sync_sessions = user.m_user->sync_manager()->get_all_sessions();
    auto session = sync_sessions[0];
    co_await realm::make_awaitable<std::error_code>([&] (auto cb) {
        session->wait_for_download_completion(cb);
    });
    co_return;
}

realm::task<realm::db_config> task;

realm::task<realm::db_config> run_realm() {
    auto app = realm::App("verizon_poc-doazc");
    //auto app = realm::App("cpp-sdk-2-pgjiz");
    auto user = co_await app.login(realm::App::Credentials::anonymous());

    auto flx_sync_config = user.flexible_sync_configuration();
    std::cout << flx_sync_config.path << std::endl;

    auto tsr = co_await realm::async_open<DVRDatum>(flx_sync_config);
    auto synced_realm = tsr.resolve();

    auto update_success = co_await synced_realm.subscriptions().update([](realm::MutableSyncSubscriptionSet& subs) {
        subs.clear();
    });

    update_success = co_await synced_realm.subscriptions().update([](realm::MutableSyncSubscriptionSet& subs) {
        subs.add<DVRDatum>("foo-strings", [](auto& obj) {
            return obj.devicehash != "somenonexistantdevicehash123"; // sync all objects where devicehash does not equal 'somenonexistantdevicehash123'
        });
    });

    std::cout << "synced_realm subscriptions size: " << synced_realm.subscriptions().size() << std::endl;
    std::cout << "update_success: " << update_success << std::endl;
    auto sub = *synced_realm.subscriptions().find("foo-strings");
    std::cout << "subscription name: " << sub.name() << std::endl;
    std::cout << "subscription object class name: " << sub.object_class_name() << std::endl;
    std::cout << "subscription query string: " << sub.query_string() << std::endl;
    
    co_await wait_for_sync_uploads(user);
    co_await wait_for_sync_downloads(user);
    synced_realm.write([]() { });  // refresh realm

    auto devices = synced_realm.objects<DVRDatum>();
    std::cout << "devices count: " << devices.size() << std::endl;
    
    update_success = co_await synced_realm.subscriptions().update([](realm::MutableSyncSubscriptionSet& subs) {
        subs.update_subscription<DVRDatum>("foo-strings");
    });

    co_await wait_for_sync_uploads(user);
    co_await wait_for_sync_downloads(user);
    synced_realm.write([]() { });  // refresh realm

    devices = synced_realm.objects<DVRDatum>();
    std::cout << "devices count DEUX: " << devices.size() << std::endl;
    
    auto dvr_device_102 = make_sample_102();
    auto dvr_device_103 = make_sample_103();

    synced_realm.write([&synced_realm, &dvr_device_102, &dvr_device_103]() {
        synced_realm.add(dvr_device_102);
        synced_realm.add(dvr_device_103);
    });

    auto token = dvr_device_102.observe<DVRDatum>([](auto&& change) {
        std::cout << "property changed" << std::endl;
    });

    co_await wait_for_sync_uploads(user);
    co_await wait_for_sync_downloads(user);

    synced_realm.write([&synced_realm, &dvr_device_102]() {
        dvr_device_102.episodename = "episode_1";
    });

    co_await wait_for_sync_uploads(user);
    co_await wait_for_sync_downloads(user);

    synced_realm.write([&synced_realm, &dvr_device_102]() {
        dvr_device_102.episodename = "episode_2";
    });

    co_await wait_for_sync_uploads(user);
    co_await wait_for_sync_downloads(user);
    
    auto more_devices = synced_realm.objects<DVRDatum>();
    std::cout << "more devices count: " << more_devices.size() << std::endl;
    
    std::vector<DVRDatum> myDevices;
    std::copy(more_devices.begin(), more_devices.end(), std::back_inserter(myDevices));
    for (auto& dev:myDevices) {
        std::cout << "device: " << dev << std::endl;
    }

    auto r = realm::thread_safe_reference<DVRDatum>(dvr_device_102);

    co_return flx_sync_config;
}


int main() {
    task = run_realm();
    while (task.handle.done() == false) { }

    auto config = task.await_resume();
    
    realm::notification_token token;
    auto db = realm::open<DVRDatum>(config);
    realm::ResultsChange<DVRDatum> dvrDatumChange;
    auto results = db.objects<DVRDatum>();
    
    realm::util::EventLoop::main().perform([c = std::move(config), &token, &db, &results, &dvrDatumChange]() {
        token = results.observe([&](realm::ResultsChange<DVRDatum> c, std::exception_ptr) {
            std::cout << "collection changed async" << std::endl;
            dvrDatumChange = std::move(c);
            std::cout << "modification count: " << dvrDatumChange.modifications.size() << std::endl;
            std::cout << "insertion count: " << dvrDatumChange.insertions.size() << std::endl;
            std::cout << "deletion count: " << dvrDatumChange.deletions.size() << std::endl;
            std::cout << "collection is empty: " << dvrDatumChange.empty() << std::endl;
            std::cout << "collection is deleted: " << dvrDatumChange.collection_root_was_deleted << std::endl;
            
            std::vector<DVRDatum> myDevices;
            std::copy(dvrDatumChange.collection->begin(), dvrDatumChange.collection->end(), std::back_inserter(myDevices));
            std::cout << "collection count: " << myDevices.size() << std::endl;
            
            // You can iterate through modification, insertions, deletions, or the full collection.
            // Here's an example of iterating through collections that have been modified.
            for (auto& index:dvrDatumChange.modifications) {
                std::cout << "mod index: " << index << std::endl;
                std::cout << "mod device: " << myDevices[index] << std::endl;
            }
        });
    });
    
    realm::util::EventLoop::main().run_until([]() {
        return false;
    });

    
// The commented code sample below shows listening for a change on an individual object.
//
//    realm::notification_token token;
//    auto db = realm::open<DVRDatum>(config);
//    auto obj = *db.objects<DVRDatum>()[0];
//
//    realm::util::EventLoop::main().perform([c = std::move(config), &token, &db, &obj]() {
//        token = obj.observe<DVRDatum>([](auto&& change) {
//            std::cout << "property changed async" << std::endl;
//            std::cout << "device: " << *(change.object) << std::endl;
//        });
//    });
//
//    realm::util::EventLoop::main().run_until([]() {
//        return false;
//    });

    return 0;
}
