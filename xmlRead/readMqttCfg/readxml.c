#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

// 打印节点的属性和内容
void print_node(xmlNode *node) {
    for (xmlNode *cur_node = node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            // 打印节点名称
            printf("Node: %s\n", cur_node->name);

            // 打印节点属性
            for (xmlAttr *attr = cur_node->properties; attr; attr = attr->next) {
                printf("  Attribute: %s = %s\n", attr->name, xmlNodeGetContent(attr->children));
            }

            // 打印节点内容（如果有）
            if (xmlNodeGetContent(cur_node->children) != NULL) {
                printf("  Content: %s\n", xmlNodeGetContent(cur_node->children));
            }

            // 递归处理子节点
            print_node(cur_node->children);
        }
    }
}

int main() {
    // 初始化 libxml2 库
    xmlInitParser();

    // 解析 XML 文件
    const char *filename = "mqttconfig.xml";
    xmlDoc *doc = xmlReadFile(filename, NULL, 0);
    if (doc == NULL) {
        fprintf(stderr, "Failed to parse %s\n", filename);
        return 1;
    }

    // 获取根节点
    xmlNode *root = xmlDocGetRootElement(doc);
    if (root == NULL) {
        fprintf(stderr, "Empty document\n");
        xmlFreeDoc(doc);
        return 1;
    }

    // 打印 XML 内容
    printf("Parsing XML file: %s\n", filename);
    print_node(root);

    // 释放资源
    xmlFreeDoc(doc);
    xmlCleanupParser();

    return 0;
}
