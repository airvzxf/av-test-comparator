# AV-TEST Comparator

Compare the best antivirus software, this application collects the results of AV-TEST and analyzes it in detail.

https://www.av-test.org

## Results on 2020-10-05 / PC Windows

The data was taken from the last 12 months.

Note: I excluded the results on April 2020 because Kaspersky and AVG not have details results, means the web page is
broken.

### 1st Place in Protection
<b>Kaspersky</b> and <b>Norton</b><br>
<b>Usability:</b> Kaspersky by 10 points.<br>
<b>Performance:</b> Norton by 64 points.

|Antivirus|Protection|Antivirus|Usability|Antivirus|Performance|
|---|---|---|---|---|---|
|Kaspersky|31200|Kaspersky|4|Norton|1005|
|Norton|31200|Norton|14|Kaspersky|1069|


### 2nd Place in Protection

|Antivirus|Protection|Antivirus|Usability|Antivirus|Performance|
|---|---|---|---|---|---|
|Bitdefender|31184|Avira|3|VIPRE Security|937|
|Trend Micro|31178|McAfee|8|McAfee|1008|
|Avast|31163|VIPRE Security|14|Bitdefender|1165|
|AVG|31159|Trend Micro|20|Avira|1208|
|Microsoft|31141|Avast|21|AhnLab|1212|
|Avira|31133|AVG|27|K7 Computing|1278|
|G Data|31113|Microsoft|28|Microsoft|1307|
|BullGuard|31106|AhnLab|30|BullGuard|1336|
|VIPRE Security|31073|BullGuard|31|Avast|1439|
|McAfee|31067|Bitdefender|33|AVG|1485|
|K7 Computing|31022|K7 Computing|40|Trend Micro|1501|
|AhnLab|31011|G Data|45|G Data|1985|


TODOs:
- [ ] Maybe create a multi-thread for get the details for every antivirus.
- [ ] Create config file for example set the type (PC, Phone, Business) and the dates looking for.
- [ ] Add functionality take the information from PC, Phone, Business.
- [ ] Generic CURL in the CMakeList to run this executable in my web hosting server.
- [x] Export the information into a CSV file.
