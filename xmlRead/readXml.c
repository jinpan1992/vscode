#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

int main() {
    // 确保libxml2版本正确
    LIBXML_TEST_VERSION

    // 读取XML文件
    xmlDocPtr doc = xmlReadFile("example.xml", NULL, 0);
    if (doc == NULL) {
        fprintf(stderr, "无法读取XML文件 test.xml\n");
        return 1;
    }

    // 获取XML文档的根元素
    xmlNodePtr root = xmlDocGetRootElement(doc);
    if (root == NULL) {
        fprintf(stderr, "文档为空\n");
        xmlFreeDoc(doc);
        return 1;
    }

    // 检查根元素的名字是否为 'root'
    if (xmlStrcmp(root->name, (const xmlChar *) "root")) {
        fprintf(stderr, "文档类型错误，根节点名称不是 'root'\n");
        xmlFreeDoc(doc);
        return 1;
    }

    // 遍历根元素的子节点
    xmlNodePtr cur = root->xmlChildrenNode;
    while (cur != NULL) {
        if (xmlStrEqual(cur->name, (const xmlChar *)"name")) {
            // 获取 'name' 元素的内容
            xmlChar *name_content = xmlNodeGetContent(cur);
            printf("Name: %s\n", name_content);
            xmlFree(name_content);
        } else if (xmlStrEqual(cur->name, (const xmlChar *)"website")) {
            // 获取 'website' 元素的内容
            xmlChar *website_content = xmlNodeGetContent(cur);
            printf("Website: %s\n", website_content);
            xmlFree(website_content);
        }
        // 寻找 'function' 元素，并遍历它的子元素
        if (xmlStrEqual(cur->name, (const xmlChar *)"function")) {
            xmlNodePtr func_cur = cur->xmlChildrenNode;
            while (func_cur != NULL) {
                if (xmlStrEqual(func_cur->name, (const xmlChar *)"json")) {
                    // 获取 'json' 元素的内容
                    xmlChar *json_content = xmlNodeGetContent(func_cur);
                    printf("JSON Endpoint: %s\n", json_content);
                    xmlFree(json_content);
                } else if (xmlStrEqual(func_cur->name, (const xmlChar *)"sql")) {
                    // 获取 'sql' 元素的内容
                    xmlChar *sql_content = xmlNodeGetContent(func_cur);
                    printf("SQL Endpoint: %s\n", sql_content);
                    xmlFree(sql_content);
                }
                func_cur = func_cur->next;
            }
        }
        cur = cur->next;
    }

    // 清理并释放文档
    xmlFreeDoc(doc);
    // 清理并结束libxml2的解析环境
    xmlCleanupParser();

    return 0;
}
