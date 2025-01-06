#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>

int ParseMqttConfig(char* configfilePATH)
{
    xmlDocPtr doc;
    xmlNodePtr curNode, Node1;
    xmlXPathContextPtr context;
    char *szDocName = configfilePATH;
    int ret = 0;

    //NORTH_PARAM_T *mqttParam = (NORTH_PARAM_T *)northMqtt;
    doc = xmlReadFile(szDocName,"UTF-8", XML_PARSE_RECOVER);

    //if (NULL == doc || mqttParam == NULL)
    if (NULL == doc)
    {
        //EMS_LOG(LL_ERROR, MODULE_T, FALSE, "Document not parsed successfully\n" );
        return -1;
    }

    context = xmlXPathNewContext(doc);
    if (context == NULL)
    {
        //EMS_LOG(LL_ERROR, MODULE_T, FALSE, "context is NULL\n");
        xmlFreeDoc(doc);
        return -1;
    }

    //读取root节点
    curNode = xmlDocGetRootElement(doc);
    if (NULL == curNode)
    {
        //EMS_LOG(LL_ERROR, MODULE_T, FALSE, "string_xml no root !\n");
        xmlXPathFreeContext(context);
        xmlFreeDoc(doc);
        return -1;
    }

    //解析root下子节点
    if (xmlStrcmp(curNode->name, BAD_CAST "root"))
    {
        //EMS_LOG(LL_ERROR, MODULE_T, FALSE, "document of the wrong type, root node != root");
        xmlXPathFreeContext(context);
        xmlFreeDoc(doc);
        return -1;
    }

    xmlNodePtr propNodePtr = curNode->xmlChildrenNode;
    Node1 = curNode->xmlChildrenNode;

    while (Node1 != NULL)
    {
        if ((!xmlStrcmp(Node1->name, (const xmlChar * ) "mqtt")))
        {
            //查找属性
            propNodePtr = Node1;
            xmlAttrPtr attrPtr = propNodePtr->properties;
            while (attrPtr != NULL)
            {
                if (!xmlStrcmp(attrPtr->name, BAD_CAST "enabled"))
                {
                    xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "enabled" );
                    if (strtoul((const char * )szAttr, NULL, 0) == 1)
                    {
                        //mqttParam->CfgSelect |= 1;
                    }
                    xmlFree(szAttr);
                }
                else if (!xmlStrcmp(attrPtr->name, BAD_CAST "host_ip"))
                {
                    xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "host_ip");
                    //strcpy(mqttParam->MqttAddr, (const char * )szAttr);
                    printf("host_ip: %s\n", (const char * )szAttr);
                    xmlFree(szAttr);
                }
                else if (!xmlStrcmp(attrPtr->name, BAD_CAST "host_port"))
                {
                    xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "host_port");
                    //mqttParam->MqttPort = strtoul((const char * )szAttr, NULL, 0);
                    printf("host_port: %s\n", (const char * )szAttr);
                    xmlFree(szAttr);
                }
                attrPtr = attrPtr->next;
            }
        }
        else if ((!xmlStrcmp(Node1->name, (const xmlChar * ) "client_id")))
        {
            xmlChar* szKey = xmlNodeGetContent(Node1);
            //strcpy(mqttParam->MqttClientID, (const char * )szKey);
            printf("client_id: %s\n", (const char * )szKey);
            xmlFree(szKey);
        }
        else if ((!xmlStrcmp(Node1->name, (const xmlChar * ) "username")))
        {
            xmlChar* szKey = xmlNodeGetContent(Node1);
            //strcpy(mqttParam->MqttUser, (const char * )szKey);
            printf("username: %s\n", (const char * )szKey);
            xmlFree(szKey);
        }
        else if ((!xmlStrcmp(Node1->name, (const xmlChar * ) "password")))
        {
            xmlChar* szKey = xmlNodeGetContent(Node1);
            //strcpy(mqttParam->MqttPwd, (const char * )szKey);
            printf("password: %s\n", (const char * )szKey);
            xmlFree(szKey);
        }
        else if((!xmlStrcmp(Node1->name, (const xmlChar * )"upload_method")))
        {
            xmlChar* szKey = xmlNodeGetContent(Node1);
            //mqttParam->MqttMethod = strtoul((const char * )szKey, NULL, 0);
            printf("upload_method: %s\n", (const char * )szKey);
            xmlFree(szKey);
        }
        else if((!xmlStrcmp(Node1->name, (const xmlChar * )"encrypt")))
        {
            //查找属性
            propNodePtr = Node1;
            xmlAttrPtr attrPtr = propNodePtr->properties;
            while (attrPtr != NULL)
            {
                if (!xmlStrcmp(attrPtr->name, BAD_CAST "enabled"))
                {
                    xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "enabled" );
                    //mqttParam->MqttEncry = strtoul((const char * )szAttr, NULL, 0);
                    printf("enabled: %s\n", (const char * )szAttr);
                    xmlFree(szAttr);
                }
                else if (!xmlStrcmp(attrPtr->name, BAD_CAST "en_method"))
                {
                    xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "en_method");
                    //mqttParam->MqttAlgor = strtoul((const char * )szAttr, NULL, 0);
                    printf("en_method: %s\n", (const char * )szAttr);
                    xmlFree(szAttr);
                }

                attrPtr = attrPtr->next;
            }
        }
        else if((!xmlStrcmp(Node1->name, (const xmlChar * )"upload_period")))
        {
            xmlChar* szKey = xmlNodeGetContent(Node1);
            //mqttParam->MqttCycle = strtoul((const char * )szKey, NULL, 0);
            printf("upload_period: %s\n", (const char * )szKey);
            xmlFree(szKey);
        }
        else if((!xmlStrcmp(Node1->name, (const xmlChar * )"topic_pub_rundata_all")))
        {
            xmlChar* szKey = xmlNodeGetContent(Node1);
            //strcpy(mqttParam->MqttPubTopic, (char *)szKey);
            printf("topic_pub_rundata_all: %s\n", (const char * )szKey);
            xmlFree(szKey);
        }
        else if((!xmlStrcmp(Node1->name, (const xmlChar * )"topic_sub_command")))
        {
            xmlChar* szKey = xmlNodeGetContent(Node1);
            //strcpy(mqttParam->MqttSubTopic, (char *)szKey);
            printf("topic_sub_command: %s\n", (const char * )szKey);
            xmlFree(szKey);
        }
        Node1 = Node1->next;
    }

    xmlXPathFreeContext(context);
    xmlFreeDoc(doc);

    return ret;
}

int main()
{
    char *filename = "mqttconfig.xml";    
    ParseMqttConfig(filename);
    
    return 0;
}
