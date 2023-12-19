// main.js
import { createApp } from 'vue';
import App from './App.vue';
import { createRouter, createWebHistory } from 'vue-router';
import ElementPlus from 'element-plus'
import 'element-plus/dist/index.css'
import * as ElementPlusIconsVue from '@element-plus/icons-vue'


import Index from './components/Index.vue';
import Add from './components/Add.vue';
import Delete from './components/Delete.vue';
import Update from './components/Update.vue';
import Query from './components/Query.vue';

const routes = [
  { path: '/', component: Index },
  { path: '/add', component: Add },
  { path: '/delete', component: Delete },
  { path: '/update', component: Update },
  { path: '/query', component: Query },
];

const router = createRouter({
  history: createWebHistory(),
  routes,
});

const app = createApp(App);

for (const [key, component] of Object.entries(ElementPlusIconsVue)) {
  app.component(key, component)
}

app.use(router);
app.use(ElementPlus)

app.mount('#app');
