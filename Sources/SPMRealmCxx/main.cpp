//
//  main.cpp
//  
//
//  Created by Lee Maguire on 28/07/2022.
//

#include <stdio.h>
#include <cpprealm/sdk.hpp>

struct FooObject: realm::object {

    realm::persisted<int> _id;
    realm::persisted<bool> bool_col;
    realm::persisted<std::string> str_col;
    realm::persisted<std::chrono::time_point<std::chrono::system_clock>> date_col;
    realm::persisted<realm::uuid> uuid_col;
    realm::persisted<std::vector<std::uint8_t>> binary_col;

    using schema = realm::schema<
    "AllTypesObject",
    realm::property<"_id", &FooObject::_id, true>,
    realm::property<"bool_col", &FooObject::bool_col>,
    realm::property<"str_col", &FooObject::str_col>,
    realm::property<"date_col", &FooObject::date_col>,
    realm::property<"uuid_col", &FooObject::uuid_col>,
    realm::property<"binary_col", &FooObject::binary_col>>;
};

realm::task<void> task;

realm::task<void> run_realm() {
    auto app = realm::App("cpp-sdk-2-pgjiz");
    auto user = co_await app.login(realm::App::Credentials::anonymous());

    auto flx_sync_config = user.flexible_sync_configuration();
    std::cout << flx_sync_config.path << std::endl;

    auto tsr = co_await realm::async_open<FooObject>(flx_sync_config);
    auto synced_realm = tsr.resolve();

    auto update_success = co_await synced_realm.subscriptions().update([](realm::MutableSyncSubscriptionSet& subs) {
        subs.clear();
    });

    update_success = co_await synced_realm.subscriptions().update([](realm::MutableSyncSubscriptionSet& subs) {
        subs.add<FooObject>("foo-strings", [](auto& obj) {
            return obj.str_col != "alex"; // sync all objects where name does not equal 'alex'
        });
    });

    auto person = FooObject();
    person._id = 1;
    person.str_col = "john";

    synced_realm.write([&synced_realm, &person]() {
        synced_realm.add(person);
    });

    auto token = person.observe<FooObject>([](auto&& change) {
        std::cout << "property changed" << std::endl;
    });

    synced_realm.write([&synced_realm, &person]() {
        person.str_col = "sarah";
    });

    synced_realm.write([&synced_realm, &person]() {
        person.str_col = "bob";
    });

    co_return;
}


int main() {
    task = run_realm();
    while (task.handle.done() == false) { }
    return 0;
}
