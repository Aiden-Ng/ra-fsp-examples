{"profileName":"Profile","qeIsCentralDevice":true,"services":[{"name":"GAP Service","uuid":["0x00","0x18"],"abbreviation":"gap","description":"The generic_access service contains generic information about the device.","aux_properties":["None"],"error_codes":[],"characteristics":[{"name":"Device Name","abbreviation":"dev name","uuid":["0x00","0x2A"],"description":"The Device Name characteristic shall contain the name of the device.","properties":["Read","Write"],"aux_properties":[],"value":"","db_size":128,"fields":[{"name":"Name","description":"Name","format":"uint8_t","length":"1","bits":[],"valueMap":[],"fields":[]}],"descriptors":[]},{"name":"Appearance","abbreviation":"appearance","uuid":["0x01","0x2A"],"description":"The Appearance characteristic defines the representation of the external appearance of the device.","properties":["Read"],"aux_properties":[],"value":"","db_size":2,"fields":[{"name":"Category","description":"Category","format":"uint16_t","length":"1","enumerations":[{"value":"Unknown","key":0,"description":"Unknown"},{"value":"Generic Phone","key":64,"description":"Generic Phone"},{"value":"Generic Computer","key":128,"description":"Generic Computer"},{"value":"Generic Watch","key":192,"description":"Generic Watch"},{"value":"Watch Sports Watch","key":193,"description":"Watch: Sports Watch"},{"value":"Generic Clock","key":256,"description":"Generic Clock"},{"value":"Generic Display","key":320,"description":"Generic Display"},{"value":"Generic Remote Control","key":384,"description":"Generic Remote Control"},{"value":"Generic Eye-glasses","key":448,"description":"Generic Eye-glasses"},{"value":"Generic Tag","key":512,"description":"Generic Tag"},{"value":"Generic Keyring","key":576,"description":"Generic Keyring"},{"value":"Generic Media Player","key":640,"description":"Generic Media Player"},{"value":"Generic Barcode Scanner","key":704,"description":"Generic Barcode Scanner"},{"value":"Generic Thermometer","key":768,"description":"Generic Thermometer"},{"value":"Thermometer Ear","key":769,"description":"Thermometer Ear"},{"value":"Generic Heart rate Sensor","key":832,"description":"Generic Heart rate Sensor"},{"value":"Heart Rate Sensor Heart Rate Belt","key":833,"description":"Heart Rate Sensor Heart Rate Belt"},{"value":"Generic Blood Pressure","key":896,"description":"Generic Blood Pressure"},{"value":"Blood Pressure Arm","key":897,"description":"Blood Pressure: Arm"},{"value":"Blood Pressure Wrist","key":898,"description":"Blood Pressure: Wrist"},{"value":"Human Interface Device","key":960,"description":"Human Interface Device (HID)"},{"value":"Keyboard","key":961,"description":"Keyboard"},{"value":"Mouse","key":962,"description":"Mouse"},{"value":"Joystick","key":963,"description":"Joystick"},{"value":"Gamepad","key":964,"description":"Gamepad"},{"value":"Digitizer Tablet","key":965,"description":"Digitizer Tablet"},{"value":"Card Reader","key":966,"description":"Card Reader"},{"value":"Digital Pen","key":967,"description":"Digital Pen"},{"value":"Barcode Scanner","key":968,"description":"Barcode Scanner"},{"value":"Generic Glucose Meter","key":1024,"description":"Generic Glucose Meter"},{"value":"Generic Running Walking Sensor","key":1088,"description":"Generic: Running Walking Sensor"},{"value":"Running Walking Sensor In Shoe","key":1089,"description":"Running Walking Sensor: In-Shoe"},{"value":"Running Walking Sensor On Shoe","key":1090,"description":"Running Walking Sensor: On-Shoe"},{"value":"Running Walking Sensor On Hip","key":1091,"description":"Running Walking Sensor: On-Hip"},{"value":"Generic: Cycling","key":1152,"description":"Generic Cycling"},{"value":"Cycling Cycling Computer","key":1153,"description":"Cycling Cycling Computer"},{"value":"Cycling Speed Sensor","key":1154,"description":"Cycling Speed Sensor"},{"value":"Cycling Cadence Sensor","key":1155,"description":"Cycling Cadence Sensor"},{"value":"Cycling Power Sensor","key":1156,"description":"Cycling: Power Sensor"},{"value":"Cycling Speed and Cadence Sensor","key":1157,"description":"Cycling Speed and Cadence Sensor"},{"value":"Generic Pulse Oximeter","key":3136,"description":"Generic Pulse Oximeter"},{"value":"Fingertip","key":3137,"description":"Fingertip"},{"value":"Wrist Worn","key":3138,"description":"Wrist Worn"},{"value":"Generic: Weight Scale","key":3200,"description":"Generic Weight Scale"},{"value":"Generic Outdoor Sports Activity","key":5184,"description":"Generic Outdoor Sports Activity"},{"value":"Location Display Device","key":5185,"description":"Location Display Device"},{"value":"Location and Navigation Display Device","key":5186,"description":"Location and Navigation Display Device"},{"value":"Location Pod","key":5187,"description":"Location Pod"},{"value":"Location and Navigation Pod","key":5188,"description":"Location and Navigation Pod"}],"valueMap":[],"fields":[]}],"descriptors":[]},{"name":"Peripheral Preferred Connection Parameters","abbreviation":"per pref conn param","uuid":["0x04","0x2A"],"description":"The Peripheral Preferred Connection Parameters (PPCP) characteristic contains the preferred connection parameters of the Peripheral","properties":["Read"],"aux_properties":[],"value":"","db_size":8,"fields":[{"name":"Minimum Connection Interval","description":"Minimum Connection Interval","format":"uint16_t","length":"1","bits":[],"valueMap":[],"fields":[]},{"name":"Maximum Connection Interval","description":"Maximum Connection Interval","format":"uint16_t","length":"1","bits":[],"valueMap":[],"fields":[]},{"name":"Slave Latency","description":"Slave Latency","format":"uint16_t","length":"1","bits":[],"valueMap":[],"fields":[]},{"name":"Connection Supervision Timeout Multiplier","description":"Connection Supervision Timeout Multiplier","format":"uint16_t","length":"1","bits":[],"valueMap":[],"fields":[]}],"descriptors":[]},{"name":"Central Address Resolution","abbreviation":"cent addr rslv","uuid":["0xA6","0x2A"],"description":"The Peripheral should check if the peer device supports address resolution by reading the Central Address Resolution characteristic.","properties":["Read"],"aux_properties":[],"value":"","db_size":1,"fields":[{"name":"Central Address Resolution Support","description":"Central Address Resolution Support","format":"uint8_t","length":"1","bits":[],"valueMap":[],"fields":[]}],"descriptors":[]},{"name":"Resolvable Private Address Only","abbreviation":"rslv priv addr only","uuid":["0xC9","0x2A"],"description":"The device should check if the peer will only use Resolvable Private Addresses (RPAs) after bonding by reading the Resolvable Private Address Only characteristic.","properties":["Read"],"aux_properties":[],"value":"","db_size":1,"fields":[{"name":"Resolvable Private Address Only","description":"Resolvable Private Address Only","format":"uint8_t","length":"1","bits":[],"valueMap":[],"fields":[]}],"descriptors":[]}],"qeServiceDataIsSigAdopted":true,"qeServiceDefinitionJsonFileName":"generic_access.service.json","qeServiceDataIsOutputServerRole":true,"qeServiceDataIsOutputClentRole":true},{"name":"GATT Service","uuid":["0x01","0x18"],"abbreviation":"gat","description":"The Generic Attribute Service contains generic information of the GATT attributes.","aux_properties":["None"],"error_codes":[],"characteristics":[{"name":"Service Changed","abbreviation":"serv chged","uuid":["0x05","0x2A"],"description":"The Service Changed characteristic is a control-point attribute that shall be used to indicate to connected devices that services have changed.","properties":["Indicate"],"aux_properties":[],"value":"","db_size":4,"fields":[{"name":"start_hdl","description":"Start of Affected Attribute Handle Range","format":"uint16_t","length":"1","bits":[],"valueMap":[],"fields":[]},{"name":"end_hdl","description":"End of Affected Attribute Handle Range","format":"uint16_t","length":"1","bits":[],"valueMap":[],"fields":[]}],"descriptors":[{"name":"Client Characteristic Configuration","abbreviation":"cli cnfg","uuid":["0x02","0x29"],"description":"Client Characteristic Configuration Descriptor","aux_properties":["Peer Specific"],"properties":["Read","Write"],"value":"","db_size":2,"fields":[{"name":"cli cnfg","description":"Client Characteristic Configuration","format":"uint16_t","length":"1","bits":[],"valueMap":[],"fields":[]}]}]}],"qeServiceDataIsSigAdopted":true,"qeServiceDefinitionJsonFileName":"generic_attribute.service.json","qeServiceDataIsOutputServerRole":false,"qeServiceDataIsOutputClentRole":true},{"name":"LED Switch Service(Custom Service)","uuid":["0xE0","0xFC","0x8E","0x8E","0x96","0xB4","0x01","0xAB","0x67","0x42","0x05","0x5F","0x26","0x19","0x83","0x58"],"abbreviation":"ls","description":"This service exposes a control point to allow a peer device to control LEDs and switched on the device.","aux_properties":["None"],"error_codes":[],"characteristics":[{"name":"Switch State","abbreviation":"switch state","uuid":["0xE0","0xFC","0x8E","0x8E","0x96","0xB4","0x01","0xAB","0x67","0x42","0x05","0x5F","0x57","0x7F","0x83","0x58"],"description":"","properties":["Notify"],"aux_properties":[],"value":"","db_size":1,"fields":[{"name":"State","format":"uint8_t","length":"1","bits":[],"valueMap":[],"fields":[]}],"descriptors":[{"name":"Client Characteristic Configuration","abbreviation":"cli cnfg","uuid":["0x02","0x29"],"description":"Client Characteristic Configuration Descriptor","aux_properties":["Peer Specific"],"properties":["Read","Write"],"value":"","db_size":2,"fields":[{"name":"cli cnfg","description":"Client Characteristic Configuration","format":"uint16_t","length":"1","bits":[],"valueMap":[],"fields":[]}]}]},{"name":"LED Blink Rate","abbreviation":"blink rate","uuid":["0xE0","0xFC","0x8E","0x8E","0x96","0xB4","0x01","0xAB","0x67","0x42","0x05","0x5F","0x2F","0xC3","0x83","0x58"],"description":"","properties":["Read","Write"],"aux_properties":[],"value":"","db_size":1,"fields":[{"name":"Rate","format":"uint8_t","length":"1","bits":[],"valueMap":[],"fields":[]}],"descriptors":[]}],"qeServiceDataIsSigAdopted":true,"qeServiceDefinitionJsonFileName":"led_switch.service.json","qeServiceDataIsOutputServerRole":false,"qeServiceDataIsOutputClentRole":true}]}