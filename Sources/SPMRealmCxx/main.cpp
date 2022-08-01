//
//  main.cpp
//
//
//  Created by Lee Maguire on 28/07/2022.
//

#include <stdio.h>
#include <cpprealm/sdk.hpp>
#include <realm/object-store/sync/sync_session.hpp>

struct DVRDatum: realm::object {

    realm::persisted<int> _id;
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
    realm::persisted<int> programid;        // not <long>
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

realm::task<void> task;

realm::task<void> run_realm() {
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
    
    auto dvr_device = DVRDatum();
    dvr_device._id = 1;
    dvr_device.devicehash = "john";

    synced_realm.write([&synced_realm, &dvr_device]() {
        synced_realm.add(dvr_device);
    });

    co_await wait_for_sync_uploads(user);
    co_await wait_for_sync_downloads(user);

    auto token = dvr_device.observe<DVRDatum>([](auto&& change) {
        std::cout << "property changed" << std::endl;
    });

    synced_realm.write([&synced_realm, &dvr_device]() {
        dvr_device.devicehash = "sarah";
    });

    co_await wait_for_sync_uploads(user);
    co_await wait_for_sync_downloads(user);

    synced_realm.write([&synced_realm, &dvr_device]() {
        dvr_device.devicehash = "bob";
    });

    co_await wait_for_sync_uploads(user);
    co_await wait_for_sync_downloads(user);

    co_return;
}


int main() {
    task = run_realm();
    while (task.handle.done() == false) { }
    return 0;
}
