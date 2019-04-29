'use strict';

var path = require( 'path' );

const CdrFlightAppsPlugin = require( path.join( global.CDR_INSTALL_DIR, '/commander/classes/CdrFlightAppsPlugin' ) ).CdrFlightAppsPlugin;

module.exports = class CfeCdrFlightAppsPlugin extends CdrFlightAppsPlugin {
    constructor(urlBase) {
        super(path.join( __dirname, 'web'));

        var content = {
        	hs: {
                shortDescription: 'Health Services',
                longDescription: 'Health Services.',
                nodes: {
                    main: {
                        type: CdrFlightAppsPlugin.ContentType.LAYOUT,
                        shortDescription: 'Main',
                        longDescription: 'Main HS.',
                        filePath: '/main.lyt'
                    },
                    cdh: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'Command and Data Handling',
                        longDescription: 'Command counters.',
                        filePath: '/cdh.pug'
                    },
                    exec: {
                        type: CdrFlightAppsPlugin.ContentType.PANEL,
                        shortDescription: 'Execution Counts',
                        longDescription: 'Execution Counts',
                        filePath: '/exec.pug'
                    }
                }
        	}
        };
        
      	this.addContent(content);
    };
};
