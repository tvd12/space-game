package com.tvd12.space_game;

import com.tvd12.ezyfox.bean.EzyBeanContext;
import com.tvd12.ezyfox.bean.EzyBeanContextBuilder;
import com.tvd12.ezyfoxserver.app.EzyAppRequestController;
import com.tvd12.ezyfoxserver.constant.EzyEventType;
import com.tvd12.ezyfoxserver.context.EzyAppContext;
import com.tvd12.ezyfoxserver.context.EzyPluginContext;
import com.tvd12.ezyfoxserver.embedded.EzyEmbeddedServer;
import com.tvd12.ezyfoxserver.ext.EzyAbstractAppEntryLoader;
import com.tvd12.ezyfoxserver.ext.EzyAbstractPluginEntryLoader;
import com.tvd12.ezyfoxserver.ext.EzyAppEntry;
import com.tvd12.ezyfoxserver.ext.EzyPluginEntry;
import com.tvd12.ezyfoxserver.setting.*;
import com.tvd12.ezyfoxserver.support.controller.EzyUserRequestAppSingletonController;
import com.tvd12.ezyfoxserver.support.entry.EzySimpleAppEntry;
import com.tvd12.ezyfoxserver.support.entry.EzySimplePluginEntry;

public class SpaceGameStartup {

    private static final String ZONE_NAME = "space-game";
    private static final String APP_NAME = "space-game";
    private static final String PLUGIN_NAME = "space-game";

    public static void main(String[] args) throws Exception {
        EzyPluginSettingBuilder pluginSettingBuilder = new EzyPluginSettingBuilder()
                .name(PLUGIN_NAME)
                .addListenEvent(EzyEventType.USER_LOGIN)
                .entryLoader(SpaceGamePluginEntryLoader.class);

        EzyAppSettingBuilder appSettingBuilder = new EzyAppSettingBuilder()
                .name(APP_NAME)
                .entryLoader(SpaceGameAppEntryLoader.class);

        EzyZoneSettingBuilder zoneSettingBuilder = new EzyZoneSettingBuilder()
                .name(ZONE_NAME)
                .application(appSettingBuilder.build())
                .plugin(pluginSettingBuilder.build());

        EzyWebSocketSettingBuilder webSocketSettingBuilder = new EzyWebSocketSettingBuilder()
                .active(false);

        EzyUdpSettingBuilder udpSettingBuilder = new EzyUdpSettingBuilder()
                .active(true);

        EzySimpleSettings settings = new EzySettingsBuilder()
                .zone(zoneSettingBuilder.build())
                .websocket(webSocketSettingBuilder.build())
                .udp(udpSettingBuilder.build())
                .build();

        EzyEmbeddedServer server = EzyEmbeddedServer.builder()
                .settings(settings)
                .build();
        server.start();
    }

    public static class SpaceGameAppEntry extends EzySimpleAppEntry {

        @Override
        protected String[] getScanableBeanPackages() {
            return new String[]{
                    "com.tvd12.space_game"
            };
        }

        @Override
        protected String[] getScanableBindingPackages() {
            return new String[]{
                    "com.tvd12.space_game"
            };
        }

        @Override
        protected void setupBeanContext(EzyAppContext context, EzyBeanContextBuilder builder) {
            builder.addProperties("application.yaml");
        }

        @Override
        protected EzyAppRequestController newUserRequestController(EzyBeanContext beanContext) {
            return EzyUserRequestAppSingletonController.builder()
                    .beanContext(beanContext)
                    .build();
        }

    }

    public static class SpaceGameAppEntryLoader extends EzyAbstractAppEntryLoader {

        @Override
        public EzyAppEntry load() {
            return new SpaceGameAppEntry();
        }

    }

    public static class SpaceGamePluginEntry extends EzySimplePluginEntry {

        @Override
        protected String[] getScanableBeanPackages() {
            return new String[]{
                    "com.tvd12.space_game"
            };
        }

        @Override
        protected void setupBeanContext(EzyPluginContext context, EzyBeanContextBuilder builder) {
            builder.addProperties("application.yaml");
        }
    }

    public static class SpaceGamePluginEntryLoader extends EzyAbstractPluginEntryLoader {

        @Override
        public EzyPluginEntry load() {
            return new SpaceGamePluginEntry();
        }
    }
}