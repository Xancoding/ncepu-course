<template>
  <Layout>
    <div class="intro-container">
      <h3>学生信息管理系统</h3>
      <p class="intro-text">
        欢迎使用我们的学生信息管理系统。这个 Web 应用旨在帮助您高效地管理学生数据。您可以执行以下操作：
      </p>
      <ul>
        <li>添加新的学生数据</li>
        <li>删除现有学生数据</li>
        <li>更新学生信息</li>
        <li>查询和检索学生详细信息</li>
      </ul>
    </div>
  </Layout>
</template>

<script>
import Layout from '@/components/Layout.vue';

export default {
  components: {
    Layout,
  },
  name: 'Index',
};
</script>

<style scoped>
/* 样式 */
.custom-heading {
  color: #3498db;
  /* 蓝色 */
  font-size: 2em;
}

.intro-container {
  border: 1px solid #ddd;
  padding: 20px;
  margin-top: 20px;
}

.intro-text {
  font-size: 1.2em;
  line-height: 1.6;
  opacity: 0.9;
}

.more-content {
  text-align: center;
  margin-top: 20px;
  font-style: italic;
  color: #555;
  /* 灰色 */
}
</style>