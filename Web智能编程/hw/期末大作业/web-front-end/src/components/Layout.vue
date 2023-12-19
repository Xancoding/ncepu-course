<!-- Layout.vue -->
<template>
  <div>
    <header>
      <h1>Student Information Management System</h1>
    </header>

    <nav>
      <router-link to="/">Home</router-link>
      <router-link to="/add">Add Data</router-link>
      <router-link to="/delete">Delete Data</router-link>
      <router-link to="/update">Update Data</router-link>
      <router-link to="/query">Query Data</router-link>
    </nav>

    <main>
      <router-view></router-view>
      <slot></slot>
    </main>

  </div>
</template>

<style scoped>
/* 共享样式 */
header {
  background-color: #3498db;
  color: #fff;
  padding: 20px;
  text-align: center;
}

nav {
  background-color: #2c3e50;
  color: #fff;
  padding: 10px;
  text-align: center;
}

nav a {
  margin: 0 10px;
  color: #fff;
  text-decoration: none;
}

main {
  padding: 20px;
}

footer {
  background-color: #3498db;
  color: #fff;
  padding: 10px;
  text-align: center;
  position: fixed;
  bottom: 0;
  width: 100%;
}
</style>
